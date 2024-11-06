#include "index.h"

struct _node_t {
    node_definition_t *definition;
    node_id_t id;
    port_t *ports;
};
