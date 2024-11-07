#include "index.h"

struct port_t {
    node_t *node;
    port_index_t index;
    port_t *opposite_port;
};
