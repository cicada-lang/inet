#include "index.h"

struct port_t {
    const node_t *node;
    port_index_t index;
    const port_t *opposite_port;
};

port_t *
port_new() {
    port_t *self = allocate(sizeof(port_t));
    self->node = NULL;
    self->index = -1;
    self->opposite_port = NULL;
    return self;
}

void
port_destroy(port_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        port_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

const node_t *
port_node(port_t *self) {
    return self->node;
}

void
port_set_node(port_t *self, node_t *node) {
    self->node = node;
}

port_index_t
port_index(port_t *self) {
    return self->index;
}

void
port_set_index(port_t *self, port_index_t index) {
    self->index = index;
}

const port_t *
port_opposite_port(port_t *self) {
    return self->opposite_port;
}
