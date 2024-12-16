#include "index.h"

static void
on_click(debug_t *self, canvas_t *canvas, uint8_t button, bool is_release) {
    (void) canvas;

    if (button == 1) {
        if (is_release) {
            self->step_button_is_pressed = false;
        } else {
            self->step_button_is_pressed = true;
        }
    }
}

void
draw_step_button(debug_t *self, canvas_t *canvas) {
    (void) self;

    size_t x = 3 * TILE;
    size_t y = 3 * TILE;

    if (self->step_button_is_pressed) {
        canvas_draw_image_button(
            canvas, x, y, "images/button-step-down-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click);
    } else {
        canvas_draw_image_button(
            canvas, x, y, "images/button-step-up-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click);
    }
}
