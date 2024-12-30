#include "index.h"

#define LOCAL_ARRAY_SIZE 64

struct frame_t {
    size_t cursor;
    const function_t *function;
    array_t *local_array;
};

frame_t *
frame_new(const function_t *function) {
    frame_t *self = new(frame_t);
    self->cursor = 0;
    self->function = function;
    self->local_array = array_new(LOCAL_ARRAY_SIZE);
    return self;
}

void
frame_destroy(frame_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        frame_t *self = *self_pointer;
        // does not own function
        array_destroy(&self->local_array);
        free(self);
        *self_pointer = NULL;
    }
}

bool
frame_is_finished(const frame_t *self) {
    return self->cursor == function_length(self->function);
}

op_t *
frame_fetch_op(frame_t *self) {
    op_t *op = function_get_op(self->function, self->cursor);
    self->cursor++;
    return op;
}

void
frame_print(const frame_t *self, file_t *file) {
    fprintf(file, "<frame>\n");

    fprintf(file, "<function>\n");
    function_print_with_cursor(self->function, file, self->cursor);
    fprintf(file, "</function>\n");

    fprintf(file, "</frame>\n");
}

value_t
frame_local_get(const frame_t *self, size_t index) {
    return array_get(self->local_array, index);
}

void
frame_local_set(frame_t *self, size_t index, value_t value) {
    array_set(self->local_array, index, value);
}
