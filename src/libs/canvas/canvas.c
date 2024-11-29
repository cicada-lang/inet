#include "index.h"

canvas_t *
canvas_new(size_t width, size_t height) {
    canvas_t *self = allocate(sizeof(canvas_t));
    self->width = width;
    self->height = height;
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

void
canvas_put_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel) {
    self->pixels[y * self->width + x] = pixel;
}

void
canvas_draw_icn(
    canvas_t *self,
    size_t x, size_t y,
    uint8_t *bytes,
    size_t width, size_t height
) {
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            for (size_t line = 0; line < 8; line++) {
                uint8_t byte = bytes[(row * 8 * width) + (col * 8 + line)];
                for (uint8_t s = 0; s < 8; s++) {
                    bool bit = ((byte << s) & 0x80) != 0;
                    if (bit) {
                        canvas_put_pixel(
                            self,
                            x + (col * 8 + s),
                            y + (row * 8 + line),
                            0xffffffff);
                    }
                }
            }
        }
    }
}
