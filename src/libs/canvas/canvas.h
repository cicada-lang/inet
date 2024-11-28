#pragma once

struct canvas_t {
    size_t width, height, scale;
    uint32_t *pixels;
};

canvas_t *canvas_new(size_t width, size_t height, size_t scale);
void canvas_destroy(canvas_t **self_pointer);
