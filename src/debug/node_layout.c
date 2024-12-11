#include "index.h"

node_layout_t *
node_layout_new(const node_t *node) {
    node_layout_t *self = new(node_layout_t);
    self->node = node;
    self->x = 0;
    self->y = 0;
    return self;
}
