#pragma once

// A vm is like a little forth inner interpreter.

struct vm_t {
    mod_t *mod;
    list_t *token_list;
    list_t *active_wire_list;
    stack_t *value_stack;
    stack_t *return_stack;
    size_t node_id_count;
    // wire and node should use managed memory,
    // because some nets have no root.
    // i simply record the pointers in vm for now.
    set_t *wire_set;
    set_t *node_set;
    size_t log_level;
};

vm_t *vm_new(mod_t *mod);
void vm_destroy(vm_t **self_pointer);

void vm_print_return_stack(const vm_t *self, file_t *file);
void vm_print_value_stack(const vm_t *self, file_t *file);
void vm_print(const vm_t *self, file_t *file);

void vm_connect_top_wire_pair(vm_t *self);
void vm_maybe_add_active_wire(vm_t *self, wire_t *first_wire, wire_t *second_wire);

node_t *vm_add_node(vm_t* self, const node_def_t *def);
void vm_delete_node(vm_t* self, node_t *node);

wire_t *vm_add_wire(vm_t* self);
void vm_delete_wire(vm_t* self, wire_t *wire);

wire_t *vm_wire_connect(vm_t* self, wire_t *first_wire, wire_t *second_wire);
