#include "index.h"

call_builtin_op_t *
call_builtin_op_new(const builtin_spec_t *builtin_spec) {
    call_builtin_op_t *self = allocate(sizeof(call_builtin_op_t));
    self->tag = CALL_BUILTIN_OP;
    self->builtin_spec = builtin_spec;
    return self;
}

call_program_op_t *
call_program_op_new(const program_spec_t *program_spec) {
    call_program_op_t *self = allocate(sizeof(call_program_op_t));
    self->tag = CALL_PROGRAM_OP;
    self->program_spec = program_spec;
    return self;
}

call_node_op_t *
call_node_op_new(const node_spec_t *node_spec) {
    call_node_op_t *self = allocate(sizeof(call_node_op_t));
    self->tag = CALL_NODE_OP;
    self->node_spec = node_spec;
    return self;
}

connect_op_t *
connect_op_new(void) {
    connect_op_t *self = allocate(sizeof(connect_op_t));
    self->tag = CONNECT_OP;
    return self;
}

use_free_wire_op_t *
use_free_wire_op_new(const node_spec_t *node_spec, port_index_t index) {
    use_free_wire_op_t *self = allocate(sizeof(use_free_wire_op_t));
    self->tag = GET_FREE_WIRE_OP;
    self->node_spec = node_spec;
    self->index = index;
    return self;
}

void
call_builtin_op_destroy(call_builtin_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        call_builtin_op_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
call_program_op_destroy(call_program_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        call_program_op_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
call_node_op_destroy(call_node_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        call_node_op_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
connect_op_destroy(connect_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        connect_op_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

void
use_free_wire_op_destroy(use_free_wire_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        use_free_wire_op_t *self = *self_pointer;
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
        case CALL_BUILTIN_OP: {
            call_builtin_op_destroy((call_builtin_op_t **) self_pointer);
            return;
        }

        case CALL_PROGRAM_OP: {
            call_program_op_destroy((call_program_op_t **) self_pointer);
            return;
        }

        case CALL_NODE_OP: {
            call_node_op_destroy((call_node_op_t **) self_pointer);
            return;
        }

        case CONNECT_OP: {
            connect_op_destroy((connect_op_t **) self_pointer);
            return;
        }

        case GET_FREE_WIRE_OP: {
            use_free_wire_op_destroy((use_free_wire_op_t **) self_pointer);
            return;
        }
        }
    }
}

void
op_print(const op_t *unknown_op, file_t *file) {
    switch (unknown_op->tag) {
    case CALL_BUILTIN_OP: {
        call_builtin_op_t *op = (call_builtin_op_t *) unknown_op;
        fprintf(file, "%s", op->builtin_spec->name);
        return;
    }

    case CALL_PROGRAM_OP: {
        call_program_op_t *op = (call_program_op_t *) unknown_op;
        fprintf(file, "%s", op->program_spec->name);
        return;
    }

    case CALL_NODE_OP: {
        call_node_op_t *op = (call_node_op_t *) unknown_op;
        fprintf(file, "%s", op->node_spec->name);
        return;
    }

    case CONNECT_OP: {
        fprintf(file, "@wire/connec");
        return;
    }

    case GET_FREE_WIRE_OP: {
        use_free_wire_op_t *op = (use_free_wire_op_t *) unknown_op;
        fprintf(file, "(%s)", op->node_spec->name);
        port_spec_t *port_spec = op->node_spec->port_specs[op->index];
        fprintf(file, "-%s", port_spec->name);
        return;
    }
    }

    assert(false);
}
