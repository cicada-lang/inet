#include "index.h"

void
canvas_fill_bottom_right(canvas_t *self, size_t x, size_t y, uint32_t pixel) {
    for (size_t j = 0; j < self->height - y; j++) {
        for (size_t i = 0; i < self->width - x; i++) {
            canvas_draw_pixel(self, x + i, y + j, pixel);
        }
    }
}

void
canvas_fill_bottom_left(canvas_t *self, size_t x, size_t y, uint32_t pixel) {
    for (size_t j = 0; j < self->height - y; j++) {
        for (size_t i = 0; i < x; i++) {
            canvas_draw_pixel(self, i, y + j, pixel);
        }
    }
}

void
canvas_fill_top_right(canvas_t *self, size_t x, size_t y, uint32_t pixel) {
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < self->width - x; i++) {
            canvas_draw_pixel(self, x + i, j, pixel);
        }
    }
}

void
canvas_fill_top_left(canvas_t *self, size_t x, size_t y, uint32_t pixel) {
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < x; i++) {
            canvas_draw_pixel(self, i, j, pixel);
        }
    }
}

void
canvas_fill_rect(canvas_t *self, size_t x, size_t y, size_t width, size_t height, uint32_t pixel) {
    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            canvas_draw_pixel(self, x + i, y + j, pixel);
        }
    }
}

void
canvas_draw_rect(canvas_t *self, size_t x, size_t y, size_t width, size_t height, size_t thickness, uint32_t pixel) {
    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            if ((i < thickness || i >= width - thickness) ||
                (j < thickness || j >= height - thickness))
            {
                canvas_draw_pixel(self, x + i, y + j, pixel);
            }

        }
    }
}
