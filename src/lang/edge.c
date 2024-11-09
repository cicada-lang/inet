#include "index.h"

struct edge_t {
    const port_t *first_port;
    const port_t *second_port;
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
