#include "index.h"

// We do not need to define data structure for `node_t` separately,
// a node exists as a double linked list of ports connecting each other,
// that have the same `node_id`.

struct _port_t {
    // node_definition_t definition;
    id_t node_id;
    port_t *prev;
    port_t *next;
    size_t index;
};
