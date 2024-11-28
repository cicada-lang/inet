#pragma once

struct canvas_t {
    uint32_t *pixels;
    size_t width;
    size_t height;
};

canvas_t *canvas_new(size_t width, size_t height);
void canvas_destroy(canvas_t **self_pointer);
