#pragma once

// A vm is like a little forth inner interpreter.

struct vm_t {
    mod_t *mod;
    list_t *active_wire_list;
    stack_t *value_stack;
    stack_t *return_stack;
    size_t node_id_count;
    size_t log_level;
    file_t *out;
    file_t *err;
};

vm_t *vm_new(mod_t *mod);
void vm_destroy(vm_t **self_pointer);

void vm_net_run(vm_t *self);
void vm_net_step(vm_t *self);
void vm_run_until(vm_t *self, size_t base_length);
void vm_step(vm_t *self);

void vm_print_return_stack(const vm_t *self, file_t *file);
void vm_print_value_stack(const vm_t *self, file_t *file);
void vm_print(const vm_t *self, file_t *file);

void vm_connect_top_wire_pair(vm_t *vm);
void vm_maybe_add_active_wire(vm_t *vm, wire_t *first_wire, wire_t *second_wire);
