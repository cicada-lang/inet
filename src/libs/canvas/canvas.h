#pragma once

struct canvas_t {
    size_t width, height;
    uint32_t *pixels;
};

canvas_t *canvas_new(size_t width, size_t height);
void canvas_destroy(canvas_t **self_pointer);

void canvas_draw_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel);
