#include "index.h"

clickable_area_t *
clickable_area_new(
    size_t x, size_t y,
    size_t width, size_t height,
    on_click_fn_t *on_click
) {
    clickable_area_t *self = new(clickable_area_t);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->on_click = on_click;
    return self;
}

void
clickable_area_destroy(clickable_area_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        clickable_area_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}
