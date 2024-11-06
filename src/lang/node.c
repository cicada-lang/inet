#include "index.h"

struct _node_t {
    node_definition_t *node_definition;
    node_id_t node_id;
    port_t *ports;
};
