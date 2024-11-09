#include "index.h"

struct op_t { op_tag_t tag; };

struct op_exe_t { op_tag_t tag; const program_spec_t *program_spec; };
struct op_app_t { op_tag_t tag; const node_spec_t *node_spec; };
struct op_con_t { op_tag_t tag; };
struct op_fpt_t { op_tag_t tag; const node_spec_t *node_spec; port_index_t index; };

op_exe_t *
op_exe_new(const program_spec_t *program_spec) {
    op_exe_t *self = allocate(sizeof(op_exe_t));
    self->tag = OP_EXE;
    self->program_spec = program_spec;
    return self;
}

op_app_t *
op_app_new(const node_spec_t *node_spec) {
    op_app_t *self = allocate(sizeof(op_app_t));
    self->tag = OP_APP;
    self->node_spec = node_spec;
    return self;
}

op_con_t *
op_con_new(void) {
    op_con_t *self = allocate(sizeof(op_con_t));
    self->tag = OP_CON;
    return self;
}

op_fpt_t *
op_fpt_new(const node_spec_t *node_spec, port_index_t index) {
    op_fpt_t *self = allocate(sizeof(op_fpt_t));
    self->tag = OP_FPT;
    self->node_spec = node_spec;
    self->index = index;
    return self;
}

void op_exe_destroy(op_exe_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_exe_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void op_app_destroy(op_app_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_app_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void op_con_destroy(op_con_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_con_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void op_fpt_destroy(op_fpt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_fpt_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}
