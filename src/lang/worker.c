#include "index.h"

// A worker is like a little forth inner interpreter.
// The `port_stack` is like the value_stack of forth,
// but in this inet every value is port, let's be pure.

struct worker_t {
    const mod_t *mod;
    list_t *active_edge_list;
    stack_t *port_stack;
    stack_t *frame_stack;
};
