#include "index.h"

struct node_t {
    const node_spec_t *spec;
    node_id_t id;
    port_t *ports;
};
