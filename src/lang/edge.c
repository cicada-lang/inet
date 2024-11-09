#include "index.h"

// `edge_t` does NOT own `first_port` and `second_port`.

struct edge_t {
    port_t *first_port;
    port_t *second_port;
};

edge_t *edge_new(void) {
    edge_t *self = allocate(sizeof(edge_t));
    return self;
}

void
edge_destroy(edge_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        edge_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

port_t *
edge_first_port(edge_t *self) {
    return self->first_port;
}

port_t *
edge_second_port(edge_t *self) {
    return self->second_port;
}
