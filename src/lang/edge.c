#include "index.h"

struct edge_t {
    const port_t *first_port;
    const port_t *second_port;
};

edge_t *edge_new(void) {
    edge_t *self = allocate(sizeof(edge_t));
    return self;
}
