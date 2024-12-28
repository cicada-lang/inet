#include "index.h"

struct function_t {
    list_t *op_list;
    size_t length;
    op_t **ops;
};

function_t *
function_new(void) {
    function_t *self = new(function_t);
    self->op_list = list_new_with((destroy_fn_t *) op_destroy);
    self->length = 0;
    self->ops = NULL;
    return self;
}

void
function_destroy(function_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        function_t *self = *self_pointer;
        list_destroy(&self->op_list);
        if (self->ops) free(self->ops);
        free(self);
        *self_pointer = NULL;
    }
}

size_t
function_length(const function_t *self) {
    return self->length;
}

void
function_add_op(function_t *self, op_t *op) {
    list_push(self->op_list, op);
}

void
function_build(function_t *self) {
    self->length = list_length(self->op_list);
    self->ops = allocate_pointers(self->length);
    size_t index = 0;
    op_t *op = list_first(self->op_list);
    while (op) {
        self->ops[index] = op;
        op = list_next(self->op_list);
        index++;
    }
}

op_t *
function_get_op(const function_t *self, size_t index) {
    return self->ops[index];
}

void
function_print(const function_t *self, file_t *file) {
    for (size_t i = 0; i < self->length; i++) {
        op_print(self->ops[i], file);
        fprintf(file, " ");
    }
}

void
function_print_with_function_counter(const function_t *self, file_t *file, size_t function_counter) {
    for (size_t i = 0; i < self->length; i++) {
        if (i == function_counter) {
            fprintf(file, "<<< ");
            op_print(self->ops[i], file);
            fprintf(file, " ");
        } else {
            op_print(self->ops[i], file);
            fprintf(file, " ");
        }
    }
}
