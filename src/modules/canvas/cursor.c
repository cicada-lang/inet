#include "index.h"

cursor_t *
cursor_new(size_t x, size_t y) {
    cursor_t *self = new(cursor_t);
    self->x = x;
    self->y = y;
    return self;
}

void
cursor_destroy(cursor_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        cursor_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}
