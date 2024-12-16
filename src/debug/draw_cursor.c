#include "index.h"

void
draw_cursor(debug_t *self, canvas_t *canvas) {
    size_t x = canvas->cursor->x;
    size_t y = canvas->cursor->y;

    if (debug_is_any_button_pressed(self)) {
        canvas_draw_image(canvas, x, y, "images/cursor-02x02.chr", TR_FG2_BLENDING);
    } else {
        canvas_draw_image(canvas, x, y, "images/cursor-02x02.chr", TR_AP_BLENDING);
    }
}
