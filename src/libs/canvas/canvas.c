#include "index.h"

canvas_t *
canvas_new(void) {
    canvas_t *self = allocate(sizeof(canvas_t));
    return self;
}

void
canvas_destroy(canvas_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

static void
canvas_init(canvas_t *self) {
    self->display = XOpenDisplay(NULL);
    assert(self->display);
    int root = DefaultRootWindow(self->display);
    int window_x = 0;
    int window_y = 0;
    uint64_t border_width = 1;
    uint64_t border_pixel = 0;
    uint64_t background_pixel = 0;
    self->window = XCreateSimpleWindow(
        self->display, root,
        window_x, window_y,
        self->width + self->padding * 2,
        self->height + self->padding * 2,
        border_width,  border_pixel,
        background_pixel);
    XSelectInput(
        self->display,
        self->window,
        ButtonPressMask |
        ButtonReleaseMask |
        PointerMotionMask |
        ExposureMask |
        KeyPressMask |
        KeyReleaseMask);
    XStoreName(self->display, self->window, self->window_name);
}

void
canvas_open(canvas_t *self) {
    canvas_init(self);
    XMapWindow(self->display, self->window);
    XFlush(self->display);

    // while (true) {}
    // while (true) {}
}
