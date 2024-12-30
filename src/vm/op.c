#include "index.h"

call_op_t *
call_op_new(const def_t *def) {
    call_op_t *self = new(call_op_t);
    self->kind = CALL_OP;
    self->def = def;
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

literal_op_t *
literal_op_new(value_t value) {
    literal_op_t *self = new(literal_op_t);
    self->kind = LITERAL_OP;
    self->value = value;
    return self;
}

void
literal_op_destroy(literal_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        literal_op_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

local_get_op_t *
local_get_op_new(size_t index) {
    local_get_op_t *self = new(local_get_op_t);
    self->kind = LOCAL_GET_OP;
    self->index = index;
    return self;
}

void
local_get_op_destroy(local_get_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        local_get_op_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

local_set_op_t *
local_set_op_new(size_t index) {
    local_set_op_t *self = new(local_set_op_t);
    self->kind = LOCAL_SET_OP;
    self->index = index;
    return self;
}

void
local_set_op_destroy(local_set_op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        local_set_op_t *self = *self_pointer;
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
        case CALL_OP: {
            call_op_destroy((call_op_t **) self_pointer);
            return;
        }

        case LITERAL_OP: {
            literal_op_destroy((literal_op_t **) self_pointer);
            return;
        }

        case LOCAL_GET_OP: {
            local_get_op_destroy((local_get_op_t **) self_pointer);
            return;
        }

        case LOCAL_SET_OP: {
            local_set_op_destroy((local_set_op_t **) self_pointer);
            return;
        }
        }
    }
}

void
op_print(const op_t *unknown_op, file_t *file) {
    switch (unknown_op->kind) {
    case CALL_OP: {
        call_op_t *op = (call_op_t *) unknown_op;
        fprintf(file, "CALL %s", def_name(op->def));
        return;
    }

    case LITERAL_OP: {
        literal_op_t *op = (literal_op_t *) unknown_op;
        fprintf(file, "LITERAL ");
        value_print(op->value, file);
        return;
    }

    case LOCAL_GET_OP: {
        local_get_op_t *op = (local_get_op_t *) unknown_op;
        fprintf(file, "LOCAL-GET %ld", op->index);
        return;
    }

    case LOCAL_SET_OP: {
        local_set_op_t *op = (local_set_op_t *) unknown_op;
        fprintf(file, "LOCAL-SET %ld", op->index);
        return;
    }
    }

    assert(false);
}
