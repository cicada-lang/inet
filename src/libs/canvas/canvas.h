#pragma once

struct canvas_t {
    Display* display;
    Window window;
    XImage* image;
    uint32_t *pixels;
    bool window_open;
    const char *window_name;
    size_t width;
    size_t height;
    bool size_changed;
};

canvas_t *canvas_new(size_t width, size_t height);
void canvas_destroy(canvas_t **self_pointer);

void canvas_open(canvas_t *self);
