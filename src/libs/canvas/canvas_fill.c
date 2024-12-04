#include "index.h"

void
canvas_fill_bottom_right(canvas_t *self, size_t x, size_t y, color_t color) {
    for (size_t j = 0; j < self->height - y; j++) {
        for (size_t i = 0; i < self->width - x; i++) {
            canvas_draw_pixel(self, x + i, y + j, color);
        }
    }
}

void
canvas_fill_bottom_left(canvas_t *self, size_t x, size_t y, color_t color) {
    for (size_t j = 0; j < self->height - y; j++) {
        for (size_t i = 0; i < x; i++) {
            canvas_draw_pixel(self, i, y + j, color);
        }
    }
}

void
canvas_fill_top_right(canvas_t *self, size_t x, size_t y, color_t color) {
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < self->width - x; i++) {
            canvas_draw_pixel(self, x + i, j, color);
        }
    }
}

void
canvas_fill_top_left(canvas_t *self, size_t x, size_t y, color_t color) {
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < x; i++) {
            canvas_draw_pixel(self, i, j, color);
        }
    }
}
