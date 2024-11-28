#pragma once

struct canvas_window_t {
    Display* display;
    Window window;
    XImage* image;
    canvas_t *canvas;
    bool window_open;
    const char *window_name;
    bool size_changed;
};

canvas_window_t *canvas_window_new(canvas_t *canvas);
// void canvas_window_destroy(canvas_window_t **self_pointer);

// void canvas_window_open(canvas_window_t *self);
