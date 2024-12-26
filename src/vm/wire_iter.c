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
wire_iter_first(wire_iter_t *self) {
    list_push(self->occurred_wire_list, self->root);

    if (self->root->opposite) {
        list_push(self->occurred_wire_list,
                  self->root->opposite);
    }

    if (self->root->opposite &&
        self->root->opposite->node)
    {
        self->node = self->root->opposite->node;
        self->index = 0;
    }

    return self->root;
}

wire_t *
wire_iter_next(wire_iter_t *self) {
    if (!self->node) return NULL;

    while (self->index < self->node->def->arity) {
        port_index_t i = self->index++;
        wire_t *wire = self->node->wires[i];

        if (list_has(self->occurred_wire_list, wire))
            continue;

        list_push(self->occurred_wire_list, wire);

        if (wire->opposite) {
            if (list_has(self->occurred_wire_list, wire->opposite))
                continue;

            list_push(self->occurred_wire_list, wire->opposite);

            if (wire->opposite->node &&
                !list_has(self->remaining_node_list, wire->opposite->node))
            {
                list_push(self->remaining_node_list, wire->opposite->node);
            }
        }

        return wire;
    }

    self->node = list_pop(self->remaining_node_list);
    self->index = 0;
    return wire_iter_next(self);
}
