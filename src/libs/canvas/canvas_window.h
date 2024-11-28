#pragma once

struct canvas_window_t {
    canvas_t *canvas;
    size_t scale;

    uint32_t *image_buffer;
    XImage* image;
    size_t width, height;

    Display* display;
    Window window;

    const char *title;
    bool is_open;
};

canvas_window_t *canvas_window_new(canvas_t *canvas, size_t scale);
void canvas_window_destroy(canvas_window_t **self_pointer);

void canvas_window_open(canvas_window_t *self);
