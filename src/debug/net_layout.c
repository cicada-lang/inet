#include "index.h"

net_layout_t *
net_layout_new(size_t x, size_t y, size_t width, size_t height) {
    net_layout_t *self = new(net_layout_t);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->revision = 0;
    self->node_layout_list =
        list_new_with((destructor_t *) node_layout_destroy);
    return self;
}

void
net_layout_destroy(net_layout_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        net_layout_t *self = *self_pointer;
        list_destroy(&self->node_layout_list);
        free(self);
        *self_pointer = NULL;
    }
}
