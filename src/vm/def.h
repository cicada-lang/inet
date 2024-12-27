#pragma once

typedef enum {
    NODE_DEF,
    PROGRAM_DEF,
    PRIMITIVE_DEF,
} def_kind_t;

struct def_t {
    def_kind_t kind;
    union {
        primitive_def_t *as_primitive_def;
        program_def_t *as_program_def;
        node_def_t *as_node_def;
    };
};

const primitive_def_t *def_as_primitive_def(const def_t *def);
const program_def_t *def_as_program_def(const def_t *def);
const node_def_t *def_as_node_def(const def_t *def);

def_t *def_from_primitive_def(primitive_def_t *primitive_def);
def_t *def_from_program_def(program_def_t *program_def);
def_t *def_from_node_def(node_def_t *node_def);

void def_destroy(def_t **self_pointer);

const char *def_name(const def_t *self);
const char *def_kind_name(def_kind_t kind);

void def_print(const def_t *self, file_t *file);
