#include "index.h"

struct wire_iter_t {
    const wire_t *root_wire;
    list_t *occurred_wire_list;
    list_t *occurred_node_list;
    list_t *remaining_node_list;
};

wire_iter_t *
wire_iter_new(const wire_t *root_wire) {
    wire_iter_t *self = new(wire_iter_t);
    self->root_wire = root_wire;
    self->occurred_wire_list = list_new();
    self->occurred_node_list = list_new();
    self->remaining_node_list = list_new();
    return self;
}

void
wire_iter_destroy(wire_iter_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        wire_iter_t *self = *self_pointer;
        list_destroy(&self->occurred_wire_list);
        list_destroy(&self->occurred_node_list);
        list_destroy(&self->remaining_node_list);
        free(self);
        *self_pointer = NULL;
    }
}
