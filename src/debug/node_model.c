#include "index.h"

node_model_t *
node_model_new(const node_t *node, vec2_t position) {
    node_model_t *self = new(node_model_t);
    self->node = node;
    self->position = position;
    self->velocity = (vec2_t) { .x = 0, .y = 0 };
    self->force = (vec2_t) { .x = 0, .y = 0 };
    return self;
}

void
node_model_destroy(node_model_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_model_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
node_model_apply_force(node_model_t *self, double cooling) {
    double dx = self->force.x * cooling;
    double dy = self->force.y * cooling;

    double x = self->position.x + dx;
    double y = self->position.y + dy;

    self->position.x = x > 0 ? x : 0;
    self->position.y = y > 0 ? y : 0;

    self->force = (vec2_t) { .x = 0, .y = 0 };
}