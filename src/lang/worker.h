#pragma once

// A worker is like a little forth inner interpreter.
// The `port_stack` is like the `value_stack` of forth,
// but in this inet every value is port, let's be pure.

struct worker_t {
    const mod_t *mod;
    list_t *active_pair_list;
    stack_t *port_stack;
    stack_t *frame_stack;
};

worker_t *worker_new(const mod_t *mod);
void worker_destroy(worker_t **self_pointer);

void worker_interact(worker_t *self);
void worker_run(worker_t *self);
void worker_step(worker_t *self, frame_t *frame);

void worker_print(const worker_t *self);
