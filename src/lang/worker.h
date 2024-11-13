#pragma once

// A worker is like a little forth inner interpreter.

struct worker_t {
    mod_t *mod;
    list_t *active_pair_list;
    stack_t *value_stack;
    stack_t *return_stack;
    bool debug;
};

worker_t *worker_new(mod_t *mod);
void worker_destroy(worker_t **self_pointer);

void worker_interact(worker_t *self);
void worker_interact_once(worker_t *self);
void worker_run(worker_t *self);
void worker_step(worker_t *self);

void worker_print_return_stack(const worker_t *self);
void worker_print_value_stack(const worker_t *self);
void worker_print(const worker_t *self);
