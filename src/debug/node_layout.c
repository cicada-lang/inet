#include "index.h"

node_layout_t *
node_layout_new(const node_t *node, size_t x, size_t y) {
    node_layout_t *self = new(node_layout_t);
    self->node = node;
    self->x = x;
    self->y = y;
    self->force = (vec2_t) { .x = 0, .y = 0 };
    return self;
}

void
node_layout_destroy(node_layout_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_layout_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
node_layout_apply_force(node_layout_t *self, double cooling) {
    int32_t dx = self->force.x * cooling;
    int32_t dy = self->force.y * cooling;

    int32_t x = self->x + dx;
    int32_t y = self->y + dy;

    self->x = x > 0 ? x : 0;
    self->y = y > 0 ? y : 0;

    self->force.x = 0;
    self->force.y = 0;
}
