#include "index.h"

call_primitive_op_t *
call_primitive_op_new(const primitive_def_t *primitive_def) {
    call_primitive_op_t *self = new(call_primitive_op_t);
    self->kind = CALL_PRIMITIVE_OP;
    self->primitive_def = primitive_def;
    return self;
}

call_program_op_t *
call_program_op_new(const program_def_t *program_def) {
    call_program_op_t *self = new(call_program_op_t);
    self->kind = CALL_PROGRAM_OP;
    self->program_def = program_def;
    return self;
}

call_node_op_t *
call_node_op_new(const node_def_t *node_def) {
    call_node_op_t *self = new(call_node_op_t);
    self->kind = CALL_NODE_OP;
    self->node_def = node_def;
    return self;
}

connect_op_t *
connect_op_new(void) {
    connect_op_t *self = new(connect_op_t);
    self->kind = CONNECT_OP;
    return self;
}

use_free_wire_op_t *
use_free_wire_op_new(const node_def_t *node_def, port_index_t index) {
    use_free_wire_op_t *self = new(use_free_wire_op_t);
    self->kind = GET_FREE_WIRE_OP;
    self->node_def = node_def;
    self->index = index;
    return self;
}

void
call_primitive_op_destroy(call_primitive_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        call_primitive_op_t *self = *self_pointer;
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
        switch (self->kind) {
        case CALL_PRIMITIVE_OP: {
            call_primitive_op_destroy((call_primitive_op_t **) self_pointer);
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
    switch (unknown_op->kind) {
    case CALL_PRIMITIVE_OP: {
        call_primitive_op_t *op = (call_primitive_op_t *) unknown_op;
        fprintf(file, "%s", op->primitive_def->name);
        return;
    }

    case CALL_PROGRAM_OP: {
        call_program_op_t *op = (call_program_op_t *) unknown_op;
        fprintf(file, "%s", op->program_def->name);
        return;
    }

    case CALL_NODE_OP: {
        call_node_op_t *op = (call_node_op_t *) unknown_op;
        fprintf(file, "%s", op->node_def->name);
        return;
    }

    case CONNECT_OP: {
        fprintf(file, "connect");
        return;
    }

    case GET_FREE_WIRE_OP: {
        use_free_wire_op_t *op = (use_free_wire_op_t *) unknown_op;
        fprintf(file, "(%s)", op->node_def->name);
        port_def_t *port_def = op->node_def->port_defs[op->index];
        fprintf(file, "-%s", port_def->name);
        return;
    }
    }

    assert(false);
}
