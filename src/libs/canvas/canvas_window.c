#include "index.h"

canvas_window_t *
canvas_window_new(canvas_t *canvas) {
    canvas_window_t *self = allocate(sizeof(canvas_window_t));
    self->canvas = canvas;
    self->window_open = true;
    self->size_changed = false;
    return self;
}
