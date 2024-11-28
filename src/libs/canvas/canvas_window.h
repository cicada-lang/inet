#pragma once

struct canvas_window_t {
    Display* display;
    Window window;
    XImage* image;
    canvas_t *canvas_t;
    bool window_open;
    const char *window_name;
    bool size_changed;
};
