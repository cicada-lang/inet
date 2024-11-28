#include "index.h"

canvas_window_t *
canvas_window_new(canvas_t *canvas) {
    canvas_window_t *self = allocate(sizeof(canvas_window_t));
    self->canvas = canvas;
    self->window_open = true;
    self->size_changed = false;
    return self;
}

void
canvas_window_destroy(canvas_window_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_window_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

static void
canvas_window_init(canvas_window_t *self) {
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
        self->canvas->width,
        self->canvas->height,
        border_width,  border_pixel,
        background_pixel);

    long event_mask =
        ButtonPressMask |
        ButtonReleaseMask |
        PointerMotionMask |
        ExposureMask |
        KeyPressMask |
        KeyReleaseMask |
        StructureNotifyMask;
    XSelectInput(self->display, self->window, event_mask);

    XClassHint *class_hint = XAllocClassHint();
    class_hint->res_name = string_dup("inet");
    class_hint->res_class = string_dup("canvas");
    XSetClassHint(self->display, self->window, class_hint);

    XStoreName(self->display, self->window, self->window_name);
}

void
canvas_window_open(canvas_window_t *self) {
    canvas_window_init(self);


}
