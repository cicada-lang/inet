#include "index.h"

call_op_t *
call_op_new(const def_t *def) {
    call_op_t *self = new(call_op_t);
    self->kind = CALL_OP_KIND;
    self->def = def;
    return self;
}

connect_op_t *
connect_op_new(void) {
    connect_op_t *self = new(connect_op_t);
    self->kind = CONNECT_OP_KIND;
    return self;
}

use_free_wire_op_t *
use_free_wire_op_new(const node_def_t *node_def, port_index_t index) {
    use_free_wire_op_t *self = new(use_free_wire_op_t);
    self->kind = GET_FREE_WIRE_OP_KIND;
    self->node_def = node_def;
    self->index = index;
    return self;
}

void
call_op_destroy(call_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        call_op_t *self = *self_pointer;
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
        case CALL_OP_KIND: {
            call_op_destroy((call_op_t **) self_pointer);
            return;
        }

        case CONNECT_OP_KIND: {
            connect_op_destroy((connect_op_t **) self_pointer);
            return;
        }

        case GET_FREE_WIRE_OP_KIND: {
            use_free_wire_op_destroy((use_free_wire_op_t **) self_pointer);
            return;
        }
        }
    }
}

void
op_print(const op_t *unknown_op, file_t *file) {
    switch (unknown_op->kind) {
    case CALL_OP_KIND: {
        call_op_t *op = (call_op_t *) unknown_op;
        fprintf(file, "%s", def_name(op->def));
        return;
    }

    case CONNECT_OP_KIND: {
        fprintf(file, "connect");
        return;
    }

    case GET_FREE_WIRE_OP_KIND: {
        use_free_wire_op_t *op = (use_free_wire_op_t *) unknown_op;
        fprintf(file, "(%s)", op->node_def->name);
        port_def_t *port_def = op->node_def->port_defs[op->index];
        fprintf(file, "-%s", port_def->name);
        return;
    }
    }

    assert(false);
}
