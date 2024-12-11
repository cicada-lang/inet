#include "index.h"

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

static void
canvas_draw_line_low(
    canvas_t *self,
    size_t x0, size_t y0,
    size_t x1, size_t y1,
    uint32_t pixel
) {
    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }

    int32_t D = (2 * dy) - dx;
    int32_t y = y0;

    for (size_t x = x0; x <= x1; x++) {
        canvas_draw_pixel(self, x, y, pixel);
        if (D > 0) {
            y = y + yi;
            D = D + (2 * (dy - dx));
        } else {
            D = D + 2*dy;
        }
    }
}

static void
canvas_draw_line_high(
    canvas_t *self,
    size_t x0, size_t y0,
    size_t x1, size_t y1,
    uint32_t pixel
) {
    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }

    int32_t D = (2 * dx) - dy;
    int32_t x = x0;

    for (size_t y = y0; y <= y1; y++) {
        canvas_draw_pixel(self, x, y, pixel);
        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        } else {
            D = D + 2*dx;
        }
    }
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
