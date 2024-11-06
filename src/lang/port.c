#include "index.h"

struct _port_t {
    node_t *node;
    port_index_t index;
    port_t *connected;
};
