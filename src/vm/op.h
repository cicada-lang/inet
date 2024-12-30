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

struct local_get_op_t {
    op_kind_t kind;
    size_t index;
};

struct local_set_op_t {
    op_kind_t kind;
    size_t index;
};

call_op_t *call_op_new(const def_t *def);
void call_op_destroy(call_op_t **self_pointer);

literal_op_t *literal_op_new(value_t value);
void literal_op_destroy(literal_op_t **self_pointer);

local_get_op_t *local_get_op_new(size_t index);
void local_get_op_destroy(local_get_op_t **self_pointer);

local_set_op_t *local_set_op_new(size_t index);
void local_set_op_destroy(local_set_op_t **self_pointer);

void op_destroy(op_t **self_pointer);

void op_print(const op_t *self, file_t *file);
