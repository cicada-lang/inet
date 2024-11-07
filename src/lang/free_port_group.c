#include "index.h"

// A `port_t` is a free port
// if it is not linked to a node
// and it's `port_index` is -1.

struct free_port_group_t {
    const node_spec_t *node_spec;
    port_t *ports;
};
