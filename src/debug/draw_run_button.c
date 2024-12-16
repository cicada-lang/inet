#include "index.h"

static void
on_click(debug_t *self, canvas_t *canvas, uint8_t button, bool is_release) {
    (void) canvas;

    if (button == 1) {
        if (is_release) {
            self->run_button_is_pressed = false;
        } else {
            self->run_button_is_pressed = true;
        }
    }
}

void
draw_run_button(debug_t *self, canvas_t *canvas) {
    size_t x = self->canvas->width - 9 * TILE;
    size_t y = self->canvas->height - 5 * TILE;

    if (self->run_button_is_pressed) {
        canvas_draw_image_button(
            canvas, x, y, "images/button-run-down-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click);
    } else {
        canvas_draw_image_button(
            canvas, x, y, "images/button-run-up-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click);
    }
}
