#include "index.h"

struct node_t {
    const node_definition_t *definition;
    const node_id_t id;
    port_t *ports;
};
