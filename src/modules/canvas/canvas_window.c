#include "index.h"

canvas_window_t *
canvas_window_new(canvas_t *canvas) {
    canvas_window_t *self = new(canvas_window_t);
    self->canvas = canvas;
    self->width = self->canvas->width * self->canvas->scale;
    self->height = self->canvas->height * self->canvas->scale;
    self->image_buffer = allocate(self->width * self->height * sizeof(uint32_t));
    self->background_pixel = 0xff000000;
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

size_t canvas_window_offset_x(canvas_window_t *self) {
    size_t image_width = self->canvas->width * self->canvas->scale;
    return (self->width - image_width) / 2;
}

size_t canvas_window_offset_y(canvas_window_t *self) {
    size_t image_height = self->canvas->height * self->canvas->scale;
    return (self->height - image_height) / 2;
}

size_t
canvas_window_adjust_x(canvas_window_t *self, size_t x) {
    // adjust `x` after centering.
    size_t offset_x = canvas_window_offset_x(self);

    if (x < offset_x)
        x = offset_x;

    if (x > self->width + offset_x)
        x = self->width + offset_x;

    return (x - offset_x) / self->canvas->scale;
}

size_t
canvas_window_adjust_y(canvas_window_t *self, size_t y) {
    // adjust `y` after centering.
    size_t offset_y = canvas_window_offset_y(self);

    if (y < offset_y)
        y = offset_y;

    if (y > self->height + offset_y)
        y = self->height + offset_y;

    return (y - offset_y) / self->canvas->scale;
}

static void canvas_window_init_display(canvas_window_t *self);
static void canvas_window_init_window(canvas_window_t *self);
static void canvas_window_init_input(canvas_window_t *self);
static void canvas_window_init_title(canvas_window_t *self);
static void canvas_window_init_cursor(canvas_window_t *self);

static void
canvas_window_init(canvas_window_t *self) {
    canvas_window_init_display(self);
    canvas_window_init_window(self);
    canvas_window_init_input(self);
    canvas_window_init_title(self);
    canvas_window_init_cursor(self);
}

void
canvas_window_init_display(canvas_window_t *self) {
    self->display = XOpenDisplay(NULL);
    assert(self->display);

    int screen = DefaultScreen(self->display);

    int width = XDisplayWidth(self->display, screen);
    int height = XDisplayHeight(self->display, screen);
    printf("[canvas_window_init_display] width:  %upx\n", width);
    printf("[canvas_window_init_display] height: %upx\n", height);

    uint32_t black_pixel = XBlackPixel(self->display, screen);
    uint32_t white_pixel = XWhitePixel(self->display, screen);
    printf("[canvas_window_init_display] black pixel: 0x%x\n", black_pixel);
    printf("[canvas_window_init_display] white pixel: 0x%x\n", white_pixel);
}

void
canvas_window_init_window(canvas_window_t *self) {
    int window_x = 0;
    int window_y = 0;
    uint64_t border_width = 1;
    uint64_t border_pixel = 0;
    uint64_t background_pixel = 0;
    self->window = XCreateSimpleWindow(
        self->display,
        XDefaultRootWindow(self->display),
        window_x, window_y,
        self->width,
        self->height,
        border_width,  border_pixel,
        background_pixel);
}

void
canvas_window_init_input(canvas_window_t *self) {
    long event_mask =
        ButtonPressMask |
        ButtonReleaseMask |
        PointerMotionMask |
        ExposureMask |
        KeyPressMask |
        KeyReleaseMask |
        StructureNotifyMask;
    XSelectInput(self->display, self->window, event_mask);
}

void
canvas_window_init_title(canvas_window_t *self) {
    XClassHint *class_hint = XAllocClassHint();
    class_hint->res_name = string_copy("bifer");
    class_hint->res_class = string_copy("canvas");
    XSetClassHint(self->display, self->window, class_hint);

    if (self->canvas->title)
        XStoreName(self->display, self->window, self->canvas->title);
}

static void
canvas_window_hide_cursor(canvas_window_t *self) {
    XColor black = {0};
    char empty[] = {0};
    Pixmap bitmap = XCreateBitmapFromData(self->display, self->window, empty, 1, 1);
    Cursor blank = XCreatePixmapCursor(self->display, bitmap, bitmap, &black, &black, 0, 0);
    XDefineCursor(self->display, self->window, blank);
    XFreeCursor(self->display, blank);
    XFreePixmap(self->display, bitmap);
}

void
canvas_window_init_cursor(canvas_window_t *self) {
    if (self->canvas->hide_system_cursor) {
        canvas_window_hide_cursor(self);
    }
}

static void
canvas_window_update_pixel(canvas_window_t *self, size_t col, size_t row) {
    // canvas should be at the center of the image.

    size_t width_scale = self->width / (self->canvas->width);
    size_t height_scale = self->height / (self->canvas->height);

    self->canvas->scale = uint_min(width_scale, height_scale);

    size_t x_offset = canvas_window_offset_x(self);
    size_t y_offset = canvas_window_offset_y(self);

    uint32_t y_start = row * self->canvas->scale;
    uint32_t x_start = col * self->canvas->scale;

    for (size_t y = y_start; y < y_start + self->canvas->scale; y++) {
        for (size_t x = x_start; x < x_start + self->canvas->scale; x++) {
            self->image_buffer[(y_offset + y) * self->width + (x_offset + x)] =
                self->canvas->pixels[row * self->canvas->width + col];
        }
    }
}

static void
canvas_window_update_image_buffer(canvas_window_t *self) {
    // update background
    for (size_t y = 0; y < self->height; y++) {
        for (size_t x = 0; x < self->width; x++) {
            self->image_buffer[y * self->width + x] =
                self->background_pixel;
        }
    }

    // update image
    for (size_t row = 0; row < self->canvas->height; row++) {
        for (size_t col = 0; col < self->canvas->width; col++) {
            canvas_window_update_pixel(self, col, row);
        }
    }
}

static void
canvas_window_update_image(canvas_window_t *self) {
    canvas_window_update_image_buffer(self);

    Visual *visual = XDefaultVisual(self->display, 0);
    uint64_t image_depth = XDefaultDepth(self->display, 0);
    int64_t image_offset = 0;
    int64_t pixel_bytes = sizeof(uint32_t);
    int64_t pixel_bits = pixel_bytes * 8;
    int64_t bytes_per_line = 0;

    if (self->image) XFree(self->image);
    self->image = XCreateImage(
        self->display, visual,
        image_depth, ZPixmap,
        image_offset,
        (char *) self->image_buffer,
        self->width, self->height,
        pixel_bits, bytes_per_line);
}

static void
canvas_window_show_image(canvas_window_t *self) {
    XPutImage(
        self->display,
        self->window,
        XDefaultGC(self->display, 0),
        self->image,
        0, 0, 0, 0,
        self->width,
        self->height);
}

static void
canvas_window_resize(canvas_window_t *self, size_t width, size_t height) {
    if ((width == self->width) &&
        (height == self->height)) {
        return;
    }

    printf("[canvas_window_resize] width:  %lupx\n", width);
    printf("[canvas_window_resize] height: %lupx\n", height);

    self->width = width;
    self->height = height;

    self->image_buffer = realloc(
        self->image_buffer,
        self->width *
        self->height *
        sizeof(uint32_t));

    canvas_window_update_image(self);
}

static void
canvas_window_receive_button(
    canvas_window_t *self,
    uint8_t button_id,
    bool is_release
) {
    size_t x = self->canvas->cursor->x;
    size_t y = self->canvas->cursor->y;

    if (self->canvas->on_click) {
        self->canvas->on_click(
            self->canvas->state,
            self->canvas,
            button_id,
            is_release);
    }

    clickable_area_t *clickable_area =
        list_first(self->canvas->clickable_area_list);

    while (clickable_area) {
        if (x >= clickable_area->x &&
            x < clickable_area->x + clickable_area->width &&
            y >= clickable_area->y &&
            y < clickable_area->y + clickable_area->height)
        {
            clickable_area->on_click(
                self->canvas->state,
                self->canvas,
                button_id,
                is_release);
            return;
        }

        clickable_area = list_next(self->canvas->clickable_area_list);
    }

    return;
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
        canvas_window_resize(self, event->width, event->height);
        return;
    }

    case KeyPress: {
        if (self->canvas->on_key) {
            XKeyPressedEvent* event = (XKeyPressedEvent*) &unknown_event;
            int group = 0;
            int level = event->state & ShiftMask ? 1 : 0;
            KeySym keysym = XkbKeycodeToKeysym(self->display, event->keycode, group, level);
            const char *key_name = XKeysymToString(keysym);
            bool is_release = false;
            self->canvas->on_key(
                self->canvas->state,
                self->canvas,
                key_name,
                is_release);
        }

        return;
    }

    case KeyRelease: {
        if (self->canvas->on_key) {
            XKeyReleasedEvent* event = (XKeyReleasedEvent*) &unknown_event;
            int group = 0;
            int level = event->state & ShiftMask ? 1 : 0;
            KeySym keysym = XkbKeycodeToKeysym(self->display, event->keycode, group, level);
            const char *key_name = XKeysymToString(keysym);
            bool is_release = true;
            self->canvas->on_key(
                self->canvas->state,
                self->canvas,
                key_name,
                is_release);
        }

        return;
    }

    case ButtonPress: {
        XButtonPressedEvent *event = (XButtonPressedEvent *)&unknown_event;
        bool is_release = false;
        canvas_window_receive_button(
            self,
            event->button,
            is_release);
        return;
    }

    case ButtonRelease: {
        XButtonPressedEvent *event = (XButtonPressedEvent *)&unknown_event;
        bool is_release = true;
        canvas_window_receive_button(
            self,
            event->button,
            is_release);
        return;
    }

    case MotionNotify: {
        XMotionEvent *event = (XMotionEvent *)&unknown_event;
        size_t x = canvas_window_adjust_x(self, int_relu(event->x));
        size_t y = canvas_window_adjust_y(self, int_relu(event->y));
        self->canvas->cursor->x = x;
        self->canvas->cursor->y = y;
        break;
    }
    }
}

static void
canvas_window_show(canvas_window_t *self) {
    XMapWindow(self->display, self->window);
    XFlush(self->display);
}

static int
frame_timerfd(size_t n) {
    // n frame per second:
    size_t ns = 1000000000 / n;
    struct timespec timespec;
    timespec.tv_sec = 0;
    timespec.tv_nsec = ns;
    struct itimerspec interval_timespec;
    interval_timespec.it_value = timespec;
    interval_timespec.it_interval = timespec;

    int timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    timerfd_settime(timerfd, 0, &interval_timespec, NULL);

    return timerfd;
}

void
canvas_window_open(canvas_window_t *self) {
    canvas_window_init(self);
    canvas_window_show(self);

    canvas_window_update_image(self);
    canvas_window_show_image(self);

    size_t nfds = 2;
    struct pollfd fds[nfds];
    fds[0].fd = XConnectionNumber(self->display);
    fds[1].fd = frame_timerfd(self->canvas->frame_rate);
    fds[0].events = fds[1].events = POLLIN;

    self->is_open = true;
    while (self->is_open) {
        if (poll(fds, nfds, 1000) <= 0) continue;

        while (XPending(self->display)) {
            canvas_window_receive(self);
        }

        if ((fds[1].revents & POLLIN) != 0) {
            uint64_t passed;
            ssize_t nbytes = read(fds[1].fd, &passed, sizeof(uint64_t));
            assert(nbytes == 8);
            canvas_window_update_image(self);
            canvas_window_show_image(self);
            if (self->canvas->on_frame) {
                self->canvas->on_frame(
                    self->canvas->state,
                    self->canvas,
                    passed);
            }
        }
    }
}
