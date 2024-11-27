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
        self->width,
        self->height,
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

    XClassHint *class_hint = XAllocClassHint();
    class_hint->res_name = string_dup("inet");
    class_hint->res_class = string_dup("canvas");
    XSetClassHint(self->display, self->window, class_hint);

    XStoreName(self->display, self->window, self->window_name);
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

    int screen_number = DefaultScreen(self->display);
    Visual *visual = DefaultVisual(self->display, screen_number);
    uint64_t image_depth = DefaultDepth(self->display, screen_number);
    int64_t image_offset = 0;
    int64_t pixel_bits = 32;
    int64_t pixel_bytes = pixel_bits / 8;
    int64_t bytes_per_line = 0;
    self->pixels = allocate(self->width * self->height * pixel_bytes);
    self->image = XCreateImage(
        self->display, visual,
        image_depth, ZPixmap, image_offset,
        self->pixels, self->width, self->height,
        pixel_bits, bytes_per_line);

    int pitch = self->width * pixel_bytes;
    for(uint64_t y = 0; y < self->height; y++) {
        char* row = self->pixels + (y * pitch);
        for(uint64_t x = 0; x < self->width; x++) {
            unsigned int* p = (unsigned int*) (row + (x * pixel_bytes));
            if(x%16 && y%16) {
                *p = 0xffffffff;
            } else {
                *p = 0;
            }
        }
    }

    GC defaultGC = DefaultGC(self->display, screen_number);
    XPutImage(self->display, self->window,
              defaultGC, self->image,
              0, 0, 0, 0,
              self->width, self->height);

    canvas_loop(self);
}
