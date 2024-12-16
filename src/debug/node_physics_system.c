#include "index.h"

node_physics_system_t *
node_physics_system_new(size_t x, size_t y, size_t width, size_t height) {
    node_physics_system_t *self = new(node_physics_system_t);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;

    self->node_model_hash = hash_new();
    hash_set_destroy_fn(self->node_model_hash, (destroy_fn_t *) node_model_destroy);
    self->evolving_step = 0;
    self->max_evolving_step = 1000;
    self->cooling_factor = 0.999;
    return self;
}

void
node_physics_system_destroy(node_physics_system_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_physics_system_t *self = *self_pointer;
        hash_destroy(&self->node_model_hash);
        free(self);
        *self_pointer = NULL;
    }
}

void
node_physics_system_update(node_physics_system_t *self) {
    if (!self->root) return;
    if (!self->root->opposite) return;
    if (!self->root->opposite->node) return;

    node_iter_t *iter = node_iter_new(self->root->opposite->node);
    hash_t *new_hash = hash_new();
    hash_set_destroy_fn(new_hash, (destroy_fn_t *) node_model_destroy);
    node_t *node = node_iter_first(iter);
    while (node) {
        node_model_t *found = hash_get(self->node_model_hash, (void *) (size_t) node->id);
        if (found) {
            hash_set(new_hash, (void *) (size_t) found->node->id, found);
        } else {
            size_t x = self->width * ((double) rand() / RAND_MAX);
            size_t y = self->height * ((double) rand() / RAND_MAX);
            node_model_t *node_model = node_model_new(node, (vec2_t) { .x = x, y = y });
            hash_set(new_hash, (void *) (size_t) node->id, node_model);
        }

        node = node_iter_next(iter);
    }
    node_iter_destroy(&iter);

    hash_destroy(&self->node_model_hash);
    self->node_model_hash = new_hash;
}

static void
node_physics_system_electrical_force(node_physics_system_t *self) {
    list_t *node_model_list = hash_value_list(self->node_model_hash);
    node_model_t *node_model = hash_first(self->node_model_hash);
    while (node_model) {
        node_model_t *node_model2 = list_first(node_model_list);
        while (node_model2) {
            if (node_model2 != node_model) {
                vec2_t force = electrical_force(
                    node_model->position,
                    node_model2->position);

                node_model->force.x += force.x;
                node_model->force.y += force.y;
            }

            node_model2 = list_next(node_model_list);
        }

        node_model = hash_next(self->node_model_hash);
    }

    list_destroy(&node_model_list);
}

static void
node_physics_system_spring_force(node_physics_system_t *self) {
    if (!self->root) return;

    wire_iter_t *iter = wire_iter_new(self->root);
    wire_t *wire = wire_iter_first(iter);
    while (wire) {
        if (wire->node &&
            wire->opposite &&
            wire->opposite->node)
        {
            node_model_t *node_model1 =
                hash_get(self->node_model_hash, (void *) (size_t) wire->node->id);
            node_model_t *node_model2 =
                hash_get(self->node_model_hash, (void *) (size_t) wire->opposite->node->id);

            vec2_t force = spring_force(
                node_model1->position,
                node_model2->position);

            node_model1->force.x += force.x;
            node_model1->force.y += force.y;

            node_model2->force.x -= force.x;
            node_model2->force.y -= force.y;

            // printf("[node_physics_system_spring_force] force.x %f, force.y: %f\n",
            //        force.x, force.y);
        }

        wire = wire_iter_next(iter);
    }
    wire_iter_destroy(&iter);
}

void
node_physics_system_evolve(node_physics_system_t *self) {
    if (self->evolving_step > self->max_evolving_step)
        return;

    self->evolving_step++;

    (void) node_physics_system_electrical_force;
    (void) node_physics_system_spring_force;

    node_physics_system_spring_force(self);
    node_physics_system_electrical_force(self);

    double cooling = pow(self->cooling_factor, self->evolving_step);
    node_model_t *node_model = hash_first(self->node_model_hash);
    while (node_model) {
        node_model->position.x += node_model->force.x * cooling;
        node_model->position.y += node_model->force.y * cooling;

        node_model->force = (vec2_t) { .x = 0, .y = 0 };

        if (node_model->position.x < 0)
            node_model->position.x = 0;

        if (node_model->position.y < 0)
            node_model->position.y = 0;

        if (node_model->position.x > self->width)
            node_model->position.x = self->width;

        if (node_model->position.y > self->height)
            node_model->position.y = self->height;

        node_model = hash_next(self->node_model_hash);
    }
}
