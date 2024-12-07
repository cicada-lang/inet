#include "index.h"

text_t *
text_new(size_t length) {
    text_t *self = new(text_t);
    self->length = length;
    self->code_points = allocate_many(length, sizeof(text_t));
    return self;
}

void
text_destroy(text_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        text_t *self = *self_pointer;
        free(self->code_points);
        *self_pointer = NULL;
    }
}
