#pragma once

// A worker is like a little forth inner interpreter.

struct worker_t {
    mod_t *mod;
    list_t *active_wire_list;
    stack_t *value_stack;
    stack_t *return_stack;
    node_id_t node_id_count;
    bool debug;
    file_t *out;
    file_t *err;
};

worker_t *worker_new(mod_t *mod);
void worker_destroy(worker_t **self_pointer);

void worker_interact(worker_t *self);
void worker_interact_once(worker_t *self);
void worker_run_until(worker_t *self, size_t base_length);
void worker_step(worker_t *self);

void worker_print_return_stack(const worker_t *self, file_t *file);
void worker_print_value_stack(const worker_t *self, file_t *file);
void worker_print(const worker_t *self, file_t *file);

void worker_connect_top_wire_pair(worker_t *worker);
void worker_maybe_add_active_wire(worker_t *worker, wire_t *first_wire, wire_t *second_wire);
