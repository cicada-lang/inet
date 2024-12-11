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

void canvas_fiil_rect_round(canvas_t *self, size_t x, size_t y, size_t width, size_t height, uint32_t pixel, roundness_t roundness) {
    if (roundness == SM_ROUNDNESS) {
        size_t thickness = 1;
        for (size_t j = 0; j < height; j++) {
            for (size_t i = 0; i < width; i++) {
                // on four corners:
                if (((thickness <= i && i < (2 * thickness)) ||
                     (width - thickness > i && i >= width - (2 * thickness))) &&
                    ((thickness <= j && j < (2 * thickness)) ||
                     (height - thickness > j && j >= height - (2 * thickness))))
                    canvas_draw_pixel(self, x + i, y + j, pixel);

                // avoid four corners:
                if (!((i < (2 * thickness) || i >= width - (2 * thickness)) &&
                      (j < (2 * thickness) || j >= height - (2 * thickness))))
                    canvas_draw_pixel(self, x + i, y + j, pixel);
            }
        }
    } else {
        fprintf(stderr, "[canvas_fill_rect_round] unknown roundness: %u\n", roundness);
        exit(1);
    }
}
