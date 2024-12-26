#pragma once

struct op_t { op_kind_t kind; };

struct call_primitive_op_t {
    op_kind_t kind;
    const primitive_def_t *primitive_def;
};

struct call_program_op_t {
    op_kind_t kind;
    const program_def_t *program_def;
};

struct call_node_op_t {
    op_kind_t kind;
    const node_def_t *node_def;
};

struct connect_op_t {
    op_kind_t kind;
};

struct use_free_wire_op_t {
    op_kind_t kind;
    const node_def_t *node_def;
    port_index_t index;
};

call_primitive_op_t *call_primitive_op_new(const primitive_def_t *primitive_def);
call_program_op_t *call_program_op_new(const program_def_t *program_def);
call_node_op_t *call_node_op_new(const node_def_t *node_def);
connect_op_t *connect_op_new(void);
use_free_wire_op_t *use_free_wire_op_new(const node_def_t *node_def, port_index_t index);

void call_primitive_op_destroy(call_primitive_op_t **self_pointer);
void call_program_op_destroy(call_program_op_t **self_pointer);
void call_node_op_destroy(call_node_op_t **self_pointer);
void connect_op_destroy(connect_op_t **self_pointer);
void use_free_wire_op_destroy(use_free_wire_op_t **self_pointer);

void op_destroy(op_t **self_pointer);

void op_print(const op_t *self, file_t *file);
