#include "index.h"

struct program_t {
    list_t *op_list;
    size_t length;
    op_t **ops;
};

program_t *
program_new(void) {
    program_t *self = allocate(sizeof(program_t));

    self->op_list = list_new();
    list_set_item_destructor(
        self->op_list, (list_item_destructor_t *) op_destroy);

    self->length = 0;
    self->ops = NULL;
    return self;
}

void
program_destroy(program_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        program_t *self = *self_pointer;
        list_destroy(&self->op_list);
        if (self->ops) free(self->ops);
        free(self);
        *self_pointer = NULL;
    }
}

size_t
program_length(const program_t *self) {
    return self->length;
}

void
program_add_op(program_t *self, op_t *op) {
    list_push(self->op_list, op);
}

void
program_build(program_t *self) {
    self->length = list_lenght(self->op_list);
    self->ops = allocate_pointers(self->length);
    size_t index = 0;
    op_t *op = list_start(self->op_list);
    while (op) {
        self->ops[index] = op;
        op = list_next(self->op_list);
        index++;
    }
}

const op_t *
program_get_op(const program_t *self, size_t index) {
    return self->ops[index];
}
