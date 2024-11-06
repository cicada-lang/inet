#include "index.h"

struct _port_t {
    // node_definition_t definition;
    id_t node_id;
    port_t *prev;
    port_t *next;
    // const word_t *name;
    // list_t *data_constructor_list;
    bool is_closed;
};
