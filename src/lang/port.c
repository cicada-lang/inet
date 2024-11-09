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
