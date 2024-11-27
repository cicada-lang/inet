#pragma once

struct canvas_t {
    Display* display;
    Window window;
    const char *window_name;
    uint64_t width;
    uint64_t height;
    uint64_t padding;
};

canvas_t *canvas_new(void);
void canvas_destroy(canvas_t **self_pointer);

void canvas_open(canvas_t *self);
