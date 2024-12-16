#include "index.h"

static void
draw_background_grid(debug_t *self, canvas_t *canvas) {
    (void) self;

    for (size_t i = 0; i < canvas->width / TILE; i++) {
        for (size_t j = 0; j < canvas->height / TILE; j++) {
            canvas_draw_pixel(canvas, i * TILE, j * TILE, 0xffff0000);
        }
    }
}

void
draw_background(debug_t *self, canvas_t *canvas, bool with_grid) {
    canvas->window->background_pixel = canvas->palette[AP_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, canvas->palette[AP_COLOR]);

    if (with_grid) draw_background_grid(self, canvas);
}
