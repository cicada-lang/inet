#include "index.h"

node_physics_t *
node_physics_new(size_t x, size_t y, size_t width, size_t height) {
    node_physics_t *self = new(node_physics_t);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->evolving_step = 0;
    self->max_evolving_step = 1000;
    self->cooling_factor = 0.999;
    return self;
}

void
node_physics_destroy(node_physics_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_physics_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
node_physics_add_more_nodes(node_physics_t *self, hash_t *node_hash, hash_t *node_model_hash) {
    node_t *node = hash_first(node_hash);
    while (node) {
        node_model_t *found = hash_get(node_model_hash, (void *) (size_t) node->id);
        if (!found) {
            size_t x = self->width * ((double) rand() / RAND_MAX);
            size_t y = self->height * ((double) rand() / RAND_MAX);
            node_model_t *node_model = node_model_new((vec2_t) { .x = x, y = y });
            hash_set(node_model_hash, (void *) (size_t) node->id, node_model);
        }

        node = hash_next(node_hash);
    }
}

static void
node_fake_spring_force(node_physics_t *self, hash_t *node_model_hash) {
    if (!self->root) return;

    wire_iter_t *iter = wire_iter_new(self->root);
    wire_t *wire = wire_iter_first(iter);
    while (wire) {
        if (wire->node &&
            wire->opposite &&
            wire->opposite->node)
        {
            node_model_t *node_model1 =
                hash_get(node_model_hash, (void *) (size_t) wire->node->id);
            node_model_t *node_model2 =
                hash_get(node_model_hash, (void *) (size_t) wire->opposite->node->id);

            vec2_t force = spring_force(
                node_model1->position,
                node_model2->position);

            node_model1->force.x += force.x;
            node_model1->force.y += force.y;

            node_model2->force.x -= force.x;
            node_model2->force.y -= force.y;

            // printf("[node_fake_spring_force] force.x %f, force.y: %f\n",
            //        force.x, force.y);
        }

        wire = wire_iter_next(iter);
    }
    wire_iter_destroy(&iter);
}

void
node_physics_simulate(node_physics_t *self, hash_t *node_model_hash) {
    if (self->evolving_step > self->max_evolving_step)
        return;

    self->evolving_step++;

    (void) node_fake_electrical_force;
    (void) node_fake_spring_force;

    node_fake_spring_force(self, node_model_hash);
    node_fake_electrical_force(self, node_model_hash);

    double cooling = pow(self->cooling_factor, self->evolving_step);
    node_model_t *node_model = hash_first(node_model_hash);
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

        node_model = hash_next(node_model_hash);
    }
}
