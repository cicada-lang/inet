#include "index.h"

canvas_t *
canvas_new(void) {
    canvas_t *self = allocate(sizeof(canvas_t));
    self->window_open = true;
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

    // XStoreName(self->display, self->window, self->window_name);
    XStoreName(self->display, self->window,
               string_append("floating ", self->window_name));
}

static void
canvas_handle_event(canvas_t *self) {
    Atom wmDelete = XInternAtom(self->display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(self->display, self->window, &wmDelete, 1);

    XEvent unknown_event;
    XNextEvent(self->display, &unknown_event);
    switch(unknown_event.type) {
    case ClientMessage: {
        XClientMessageEvent* event = (XClientMessageEvent*) &unknown_event;
        if ((Atom)event->data.l[0] == wmDelete) {
            self->window_open = false;
            XDestroyWindow(self->display, self->window);
        }
        break;
    }
    }
}

static void
canvas_loop(canvas_t *self) {
    while (self->window_open) {
        while (XPending(self->display))
            canvas_handle_event(self);
    }
}

void
canvas_open(canvas_t *self) {
    canvas_init(self);
    XMapWindow(self->display, self->window);
    XFlush(self->display);
    canvas_loop(self);
}
