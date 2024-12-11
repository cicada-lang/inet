#include "index.h"

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
            if ((i < thickness || i >= width - thickness) ||
                (j < thickness || j >= height - thickness))
            {
                canvas_draw_pixel(self, x + i, y + j, pixel);
            }

        }
    }
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
                // on four corners:
                if (((thickness <= i && i < (2 * thickness)) ||
                     (width - thickness > i && i >= width - (2 * thickness))) &&
                    ((thickness <= j && j < (2 * thickness)) ||
                     (height - thickness > j && j >= height - (2 * thickness))))
                    canvas_draw_pixel(self, x + i, y + j, pixel);

                // one four sides:
                if ((i < thickness || i >= width - thickness) ||
                    (j < thickness || j >= height - thickness))
                {
                    // avoid four corners:
                    if (!((i < (2 * thickness) || i >= width - (2 * thickness)) &&
                          (j < (2 * thickness) || j >= height - (2 * thickness))))
                        canvas_draw_pixel(self, x + i, y + j, pixel);
                }
            }
        }
    } else {
        fprintf(stderr, "[canvas_draw_rect_round] unknown roundness: %u\n", roundness);
        exit(1);
    }
}
