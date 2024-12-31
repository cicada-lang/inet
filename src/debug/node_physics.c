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
node_physics_add_nodes(
    node_physics_t *self,
    hash_t *node_hash,
    hash_t *node_model_hash
) {
    node_t *node = hash_first(node_hash);
    while (node) {
        node_model_t *found = hash_get(node_model_hash, (void *) node->id);
        if (!found) {
            node_model_t *node_model = node_model_new((vec2_t) {
                    .x = self->width * ((double) rand() / RAND_MAX),
                    .y = self->height * ((double) rand() / RAND_MAX),
                });
            hash_set(node_model_hash, (void *) node->id, node_model);
        }

        node = hash_next(node_hash);
    }
}

void
node_physics_update_nodes(
    node_physics_t *self,
    hash_t *new_node_hash,
    hash_t *old_node_hash,
    hash_t *node_model_hash
) {
    node_t *old_node = hash_first(old_node_hash);
    while (old_node) {
        node_model_t *found = hash_get(new_node_hash, (void *) old_node->id);
        if (!found) hash_delete(node_model_hash, (void *) old_node->id);
        old_node = hash_next(old_node_hash);
    }

    node_physics_add_nodes(self, new_node_hash, node_model_hash);
}

static void
keep_node_model_in_box(node_physics_t *self, node_model_t *node_model) {
    if (node_model->position.x < 0)
        node_model->position.x = 0;

    if (node_model->position.y < 0)
        node_model->position.y = 0;

    if (node_model->position.x > self->width)
        node_model->position.x = self->width;

    if (node_model->position.y > self->height)
        node_model->position.y = self->height;
}

// fake force use force as velocity.

void
node_physics_fake_simulate(node_physics_t *self, hash_t *node_hash, hash_t *node_model_hash) {
    if (self->evolving_step > self->max_evolving_step) return;
    self->evolving_step++;

    node_fake_spring_force(self, node_hash, node_model_hash);
    node_fake_electrical_force(self, node_hash, node_model_hash);

    double cooling = pow(self->cooling_factor, self->evolving_step);
    node_model_t *node_model = hash_first(node_model_hash);
    while (node_model) {
        node_model->position.x += node_model->force.x * cooling;
        node_model->position.y += node_model->force.y * cooling;
        node_model->force = (vec2_t) { .x = 0, .y = 0 };
        keep_node_model_in_box(self, node_model);
        node_model = hash_next(node_model_hash);
    }
}
