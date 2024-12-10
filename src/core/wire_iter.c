#include "index.h"

struct wire_iter_t {
    wire_t *root;
    list_t *occurred_wire_list;
    list_t *remaining_node_list;
    node_t *node;
    port_index_t index;
};

wire_iter_t *
wire_iter_new(wire_t *root) {
    wire_iter_t *self = new(wire_iter_t);
    self->root = root;
    self->occurred_wire_list = list_new();
    self->remaining_node_list = list_new();
    return self;
}

void
wire_iter_destroy(wire_iter_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        wire_iter_t *self = *self_pointer;
        list_destroy(&self->occurred_wire_list);
        list_destroy(&self->remaining_node_list);
        free(self);
        *self_pointer = NULL;
    }
}

wire_t *
wire_iter_start(wire_iter_t *self) {
    list_push(self->occurred_wire_list, self->root);

    if (self->root->opposite_wire) {
        list_push(self->occurred_wire_list,
                  self->root->opposite_wire);
    }

    if (self->root->opposite_wire &&
        self->root->opposite_wire->node)
    {
        self->node = self->root->opposite_wire->node;
        self->index = 0;
    }

    return self->root;
}

// wire_t *
// wire_iter_next(wire_iter_t *self) {
// }
