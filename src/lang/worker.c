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

worker_t *
worker_new(const mod_t *mod) {
    worker_t *self = allocate(sizeof(worker_t));
    self->mod = mod;

    self->active_edge_list = list_new();
    list_set_item_destructor(
        self->active_edge_list,
        (list_item_destructor_t *) edge_destroy);

    self->port_stack = stack_new(10000);
    stack_set_item_destructor(
        self->port_stack,
        (stack_item_destructor_t *) port_destroy);

    self->frame_stack = stack_new(10000);
    // stack_set_item_destructor(
    //     self->frame_stack,
    //     (stack_item_destructor_t *) frame_destroy);

    return self;
}
