#include "index.h"

canvas_window_t *
canvas_window_new(canvas_t *canvas) {
    canvas_window_t *self = allocate(sizeof(canvas_window_t));
    self->canvas = canvas;
    self->image_buffer = allocate(
        self->canvas->width *
        self->canvas->height *
        self->canvas->scale *
        self->canvas->scale *
        sizeof(uint32_t));

    self->width = self->canvas->width * self->canvas->scale;
    self->height = self->canvas->height * self->canvas->scale;

    self->window_open = true;
    self->size_changed = false;
    return self;
}

void
canvas_window_destroy(canvas_window_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_window_t *self = *self_pointer;
        free(self->image_buffer);
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
        self->width,
        self->height,
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

static void
canvas_window_receive(canvas_window_t *self) {
    Atom wmDelete = XInternAtom(self->display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(self->display, self->window, &wmDelete, 1);

    XEvent unknown_event;
    XNextEvent(self->display, &unknown_event);
    switch(unknown_event.type) {
    case ClientMessage: {
        XClientMessageEvent* event = (XClientMessageEvent *) &unknown_event;
        if ((Atom)event->data.l[0] == wmDelete) {
            self->window_open = false;
            XDestroyWindow(self->display, self->window);
        }
        return;
    }

    case Expose: {
        XPutImage(
            self->display, self->window,
            DefaultGC(self->display, 0),
            self->image,
            0, 0, 0, 0,
            self->width,
            self->height);
        return;
    }

    case ConfigureNotify: {
        XConfigureEvent* event = (XConfigureEvent *) &unknown_event;
        self->width = event->width;
        self->height = event->height;
        self->size_changed = true;
        printf("[ConfigureNotify] width: %lu, height: %lu\n",
               self->width,
               self->height);
        return;
    }
    }
}

static void
canvas_window_draw(canvas_window_t *self) {
    Visual *visual = DefaultVisual(self->display, 0);
    uint64_t image_depth = DefaultDepth(self->display, 0);
    int64_t image_offset = 0;
    int64_t pixel_bytes = sizeof(uint32_t);
    int64_t pixel_bits = pixel_bytes * 8;
    int64_t bytes_per_line = 0;

    self->image = XCreateImage(
        self->display, visual,
        image_depth, ZPixmap, image_offset,
        (char *) self->image_buffer,
        self->width,
        self->height,
        pixel_bits, bytes_per_line);

    for (size_t y = 0; y < self->height; y++) {
        for (size_t x = 0; x < self->width; x++) {
            if ((x % 16 == 0) && (y % 16 == 0)) {
                self->image_buffer[y * self->width + x] = 0xffffffff;
            } else {
                self->image_buffer[y * self->width + x] = 0;
            }
        }
    }
}

void
canvas_window_open(canvas_window_t *self) {
    canvas_window_init(self);

    XMapWindow(self->display, self->window);
    XFlush(self->display);

    canvas_window_draw(self);

    while (self->window_open) {
        while (XPending(self->display)) {
            canvas_window_receive(self);
        }

        if (self->size_changed) {
            self->size_changed = false;
            self->image_buffer = realloc(
                self->image_buffer,
                self->width * self->height * sizeof(uint32_t));
            canvas_window_draw(self);
        }
    }
}
