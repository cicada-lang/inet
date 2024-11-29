#pragma once

struct canvas_t {
    size_t width, height;
    uint32_t *pixels;
};

canvas_t *canvas_new(size_t width, size_t height);
void canvas_destroy(canvas_t **self_pointer);

void canvas_put_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel);
void canvas_draw_icn(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height);
