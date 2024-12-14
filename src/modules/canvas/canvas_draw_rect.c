#include "index.h"

bool
on_rect_boundary(size_t x, size_t y, size_t width, size_t height, size_t thickness) {
return ((x < thickness || x >= width - thickness) ||
        (y < thickness || y >= height - thickness));
}

void
canvas_draw_rect(
    canvas_t *self,
    size_t x,
    size_t y,
    size_t width,
    size_t height,
    size_t thickness,
    uint32_t pixel
) {
    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            if (on_rect_boundary(i, j, width, height, thickness))
                canvas_draw_pixel(self, x + i, y + j, pixel);
        }
    }
}

bool
on_rect_sm_round_corner(size_t x, size_t y, size_t width, size_t height, size_t thickness) {
    return (((thickness <= x && x < (2 * thickness)) ||
             (width - thickness > x && x >= width - (2 * thickness))) &&
            ((thickness <= y && y < (2 * thickness)) ||
             (height - thickness > y && y >= height - (2 * thickness))));
}

bool
outside_rect_sm_round_corner(size_t x, size_t y, size_t width, size_t height, size_t thickness) {
    return ((x < (2 * thickness) || x >= width - (2 * thickness)) &&
            (y < (2 * thickness) || y >= height - (2 * thickness)));
}

void
canvas_draw_rect_round(
    canvas_t *self,
    size_t x,
    size_t y,
    size_t width,
    size_t height,
    size_t thickness,
    uint32_t pixel,
    roundness_t roundness
) {
    if (roundness == SM_ROUNDNESS) {
        for (size_t j = 0; j < height; j++) {
            for (size_t i = 0; i < width; i++) {
                if (on_rect_sm_round_corner(i, j, width, height, thickness))
                    canvas_draw_pixel(self, x + i, y + j, pixel);

                if (on_rect_boundary(i, j, width, height, thickness) &&
                    !outside_rect_sm_round_corner(i, j, width, height, thickness))
                    canvas_draw_pixel(self, x + i, y + j, pixel);
            }
        }
    } else {
        fprintf(stderr, "[canvas_draw_rect_round] unknown roundness: %u\n",
                roundness);
        exit(1);
    }
}
