#pragma once

struct op_t { op_kind_t kind; };

struct call_op_t {
    op_kind_t kind;
    const def_t *def;
};

struct literal_op_t {
    op_kind_t kind;
    value_t value;
};

struct connect_op_t {
    op_kind_t kind;
};

struct use_free_wire_op_t {
    op_kind_t kind;
    const node_def_t *node_def;
    port_index_t index;
};

call_op_t *call_op_new(const def_t *def);
void call_op_destroy(call_op_t **self_pointer);

literal_op_t *literal_op_new(value_t value);
void literal_op_destroy(literal_op_t **self_pointer);

connect_op_t *connect_op_new(void);
void connect_op_destroy(connect_op_t **self_pointer);

use_free_wire_op_t *use_free_wire_op_new(const node_def_t *node_def, port_index_t index);
void use_free_wire_op_destroy(use_free_wire_op_t **self_pointer);

void op_destroy(op_t **self_pointer);

void op_print(const op_t *self, file_t *file);
