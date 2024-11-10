#include "index.h"

op_call_program_t *
op_call_program_new(const program_spec_t *program_spec) {
    op_call_program_t *self = allocate(sizeof(op_call_program_t));
    self->tag = OP_CALL_PROGRAM;
    self->program_spec = program_spec;
    return self;
}

op_call_node_t *
op_call_node_new(const node_spec_t *node_spec) {
    op_call_node_t *self = allocate(sizeof(op_call_node_t));
    self->tag = OP_CALL_NODE;
    self->node_spec = node_spec;
    return self;
}

op_connect_t *
op_connect_new(void) {
    op_connect_t *self = allocate(sizeof(op_connect_t));
    self->tag = OP_CONNECT;
    return self;
}

op_get_free_port_t *
op_get_free_port_new(const node_spec_t *node_spec, port_index_t index) {
    op_get_free_port_t *self = allocate(sizeof(op_get_free_port_t));
    self->tag = OP_GET_FREE_PORT;
    self->node_spec = node_spec;
    self->index = index;
    return self;
}

void
op_call_program_destroy(op_call_program_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_call_program_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
op_call_node_destroy(op_call_node_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_call_node_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
op_connect_destroy(op_connect_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_connect_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
op_get_free_port_destroy(op_get_free_port_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_get_free_port_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
op_destroy(op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_t *self = *self_pointer;
        switch (self->tag) {
        case OP_CALL_PROGRAM: {
            op_call_program_destroy((op_call_program_t **) self_pointer);
            return;
        }
        case OP_CALL_NODE: {
            op_call_node_destroy((op_call_node_t **) self_pointer);
            return;
        }
        case OP_CONNECT: {
            op_connect_destroy((op_connect_t **) self_pointer);
            return;
        }
        case OP_GET_FREE_PORT: {
            op_get_free_port_destroy((op_get_free_port_t **) self_pointer);
            return;
        }
        }
    }
}
