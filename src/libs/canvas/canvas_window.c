#include "index.h"

canvas_window_t *
canvas_window_new(canvas_t *canvas, size_t scale) {
    canvas_window_t *self = allocate(sizeof(canvas_window_t));
    self->canvas = canvas;
    self->scale = scale;

    self->image_buffer = allocate(
        self->canvas->width *
        self->canvas->height *
        self->scale *
        self->scale *
        sizeof(uint32_t));

    self->width = self->canvas->width * self->scale;
    self->height = self->canvas->height * self->scale;

    return self;
}

void
canvas_window_destroy(canvas_window_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_window_t *self = *self_pointer;
        if (self->image) XFree(self->image);
        free(self->image_buffer);
        free(self);
        *self_pointer = NULL;
    }
}

static void
canvas_window_init(canvas_window_t *self) {
    self->display = XOpenDisplay(NULL);
    assert(self->display);

    int window_x = 0;
    int window_y = 0;
    uint64_t border_width = 1;
    uint64_t border_pixel = 0;
    uint64_t background_pixel = 0;
    self->window = XCreateSimpleWindow(
        self->display,
        DefaultRootWindow(self->display),
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

    if (self->title)
        XStoreName(self->display, self->window, self->title);
}


static void
canvas_window_update_pixel(canvas_window_t *self, size_t col, size_t row) {
    uint32_t pixel = self->canvas->pixels[row * self->canvas->width + col];
    uint32_t y_start = row * self->scale;
    uint32_t x_start = col * self->scale;
    uint32_t x_width = self->canvas->width * self->scale;
    for (size_t y = y_start; y < y_start + self->scale; y++) {
        for (size_t x = x_start; x < x_start + self->scale; x++) {
            self->image_buffer[y * x_width + x] = pixel;
        }
    }
}

static void
canvas_window_update_image_buffer(canvas_window_t *self) {
    for (size_t row = 0; row < self->canvas->height; row++) {
        for (size_t col = 0; col < self->canvas->width; col++) {
            canvas_window_update_pixel(self, col, row);
        }
    }
}

static void
canvas_window_update_image(canvas_window_t *self) {
    canvas_window_update_image_buffer(self);

    Visual *visual = DefaultVisual(self->display, 0);
    uint64_t image_depth = DefaultDepth(self->display, 0);
    int64_t image_offset = 0;
    int64_t pixel_bytes = sizeof(uint32_t);
    int64_t pixel_bits = pixel_bytes * 8;
    int64_t bytes_per_line = 0;

    if (self->image) XFree(self->image);
    self->image = XCreateImage(
        self->display, visual,
        image_depth, ZPixmap, image_offset,
        (char *) self->image_buffer,
        self->canvas->width * self->scale,
        self->canvas->height * self->scale,
        pixel_bits, bytes_per_line);
}

static void
canvas_window_resize(canvas_window_t *self, size_t width, size_t height) {
    self->width = width;
    self->height = height;

    size_t width_scale = self->width / self->canvas->width;
    size_t height_scale = self->height / self->canvas->height;
    self->scale = uint_min(width_scale, height_scale);

    self->image_buffer = realloc(
        self->image_buffer,
        self->canvas->width *
        self->canvas->height *
        self->scale *
        self->scale *
        sizeof(uint32_t));

    canvas_window_update_image(self);
}

static void
canvas_window_show_image(canvas_window_t *self) {
    size_t image_width = self->canvas->width * self->scale;
    size_t image_height = self->canvas->height * self->scale;

    size_t x_offset = (self->width - image_width) / 2;
    size_t y_offset = (self->height - image_height) / 2;

    XPutImage(
        self->display, self->window,
        DefaultGC(self->display, 0),
        self->image,
        0, 0,
        x_offset, y_offset,
        self->width,
        self->height);
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
            self->is_open = false;
            XDestroyWindow(self->display, self->window);
        }
        return;
    }

    case Expose: {
        canvas_window_show_image(self);
        return;
    }

    case ConfigureNotify: {
        XConfigureEvent* event = (XConfigureEvent *) &unknown_event;
        // printf("[ConfigureNotify] width: %lu, height: %lu\n",
        //        self->width,
        //        self->height);
        canvas_window_resize(self, event->width, event->height);
        return;
    }
    }
}

static void
canvas_window_show(canvas_window_t *self) {
    XMapWindow(self->display, self->window);
    XFlush(self->display);
}

void
canvas_window_open(canvas_window_t *self) {
    canvas_window_init(self);
    canvas_window_show(self);

    self->is_open = true;
    while (self->is_open) {
        while (XPending(self->display)) {
            canvas_window_receive(self);
        }
    }
}
