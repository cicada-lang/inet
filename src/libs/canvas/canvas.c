#include "index.h"

canvas_t *
canvas_new(size_t width, size_t height, size_t scale) {
    canvas_t *self = allocate(sizeof(canvas_t));
    self->width = width;
    self->height = height;
    self->scale = scale;
    self->pixels = allocate(self->width * self->height * sizeof(uint32_t));
    return self;
}

void
canvas_destroy(canvas_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_t *self = *self_pointer;
        free(self->pixels);
        free(self);
        *self_pointer = NULL;
    }
}
