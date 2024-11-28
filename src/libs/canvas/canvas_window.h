#pragma once

struct canvas_window_t {
    canvas_t *canvas;
    uint32_t *image_buffer;
    XImage* image;
    size_t width, height;

    Display* display;
    Window window;
    bool window_open;
    const char *window_name;
    bool size_changed;
};

canvas_window_t *canvas_window_new(canvas_t *canvas);
void canvas_window_destroy(canvas_window_t **self_pointer);

void canvas_window_open(canvas_window_t *self);
