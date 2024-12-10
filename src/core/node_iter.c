#include "index.h"

struct node_iter_t {
    node_t *root;
    list_t *occurred_node_list;
    list_t *remaining_node_list;
};
