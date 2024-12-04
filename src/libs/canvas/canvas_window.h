#pragma once

struct canvas_window_t {
    canvas_t *canvas;

    uint32_t *image_buffer;
    XImage* image;
    uint32_t background_pixel;

    Display* display;
    Window window;
    // The window size is messured by pixel.
    size_t width, height;
    bool is_open;
};

canvas_window_t *canvas_window_new(canvas_t *canvas);
void canvas_window_destroy(canvas_window_t **self_pointer);

void canvas_window_open(canvas_window_t *self);
