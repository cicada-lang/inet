#include "index.h"

struct _worker_t {
    mod_t *mod;
    port_stack_t *port_stack;
    list_t *active_edge_list;
};
