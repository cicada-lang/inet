#include "index.h"

struct wire_iter_t {
    list_t *occurred_wire_list;
    list_t *occurred_node_list;
    list_t *remaining_node_list;
};
