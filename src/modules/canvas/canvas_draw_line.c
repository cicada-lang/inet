#include "index.h"

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

static void
canvas_draw_line_low(
    canvas_t *self,
    size_t x0, size_t y0,
    size_t x1, size_t y1,
    uint32_t pixel
) {
    (void) self;
    (void) x0;
    (void) y0;
    (void) x1;
    (void) y1;
    (void) pixel;
}

static void
canvas_draw_line_high(
    canvas_t *self,
    size_t x0, size_t y0,
    size_t x1, size_t y1,
    uint32_t pixel
) {
    (void) self;
    (void) x0;
    (void) y0;
    (void) x1;
    (void) y1;
    (void) pixel;
}

void
canvas_draw_line(
    canvas_t *self,
    size_t x0, size_t y0,
    size_t x1, size_t y1,
    uint32_t pixel
) {
    if (abs((int32_t) y1 - (int32_t)y0) < abs((int32_t)x1 - (int32_t)x0))
        if (x0 > x1)
            canvas_draw_line_low(self, x1, y1, x0, y0, pixel);
        else
            canvas_draw_line_low(self, x0, y0, x1, y1, pixel);
    else
        if (y0 > y1)
            canvas_draw_line_high(self, x1, y1, x0, y0, pixel);
        else
            canvas_draw_line_high(self, x0, y0, x1, y1, pixel);
}
