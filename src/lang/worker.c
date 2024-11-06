#include "index.h"

struct worker_t {
    mod_t *mod;
    port_stack_t *port_stack;
    list_t *active_edge_list;
};
