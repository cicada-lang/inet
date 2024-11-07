#include "index.h"

// A worker is like a little forth inner interpreter.
// The `port_stack` is like the value_stack of forth,
// but in this inet every value is port, let's be pure.

struct worker_t {
    mod_t *mod;
    list_t *active_edge_list;
    port_stack_t *port_stack;
};
