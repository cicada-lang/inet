#pragma once

struct op_t { op_tag_t tag; };

struct call_builtin_op_t {
    op_tag_t tag;
    const builtin_spec_t *builtin_spec;
};

struct call_program_op_t {
    op_tag_t tag;
    const program_spec_t *program_spec;
};

struct call_node_op_t {
    op_tag_t tag;
    const node_spec_t *node_spec;
};

struct connect_op_t {
    op_tag_t tag;
};

struct use_free_wire_op_t {
    op_tag_t tag;
    const node_spec_t *node_spec;
    port_index_t index;
};

call_builtin_op_t *call_builtin_op_new(const builtin_spec_t *builtin_spec);
call_program_op_t *call_program_op_new(const program_spec_t *program_spec);
call_node_op_t *call_node_op_new(const node_spec_t *node_spec);
connect_op_t *connect_op_new(void);
use_free_wire_op_t *use_free_wire_op_new(const node_spec_t *node_spec, port_index_t index);

void call_builtin_op_destroy(call_builtin_op_t **self_pointer);
void call_program_op_destroy(call_program_op_t **self_pointer);
void call_node_op_destroy(call_node_op_t **self_pointer);
void connect_op_destroy(connect_op_t **self_pointer);
void use_free_wire_op_destroy(use_free_wire_op_t **self_pointer);

void op_destroy(op_t **self_pointer);

void op_print(const op_t *self, file_t *file);
