#include "index.h"

static void
on_click(debug_t *self, canvas_t *canvas, uint8_t button, bool is_release) {
    (void) canvas;

    if (button == 1) {
        if (is_release) {
            self->step_button_is_pressed = false;

            worker_net_step(self->worker);
            debug_update(self);
        } else {
            self->step_button_is_pressed = true;
        }
    }
}

void
draw_step_button(debug_t *self, canvas_t *canvas) {
    size_t x = self->canvas->width - 5 * TILE;
    size_t y = self->canvas->height - 5 * TILE;

    if (self->step_button_is_pressed) {
        canvas_draw_image_button(
            canvas, x, y, "images/step-button-down-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click);
    } else {
        canvas_draw_image_button(
            canvas, x, y, "images/step-button-up-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click);
    }
}
