#include "index.h"

canvas_t *
canvas_new(void) {
    canvas_t *self = allocate(sizeof(canvas_t));
    return self;
}

void
canvas_destroy(canvas_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}
