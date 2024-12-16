#include "index.h"

static void
on_click_step_button(debug_t *self, canvas_t *canvas, uint8_t button, bool is_release) {
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

static void
draw_step_button(debug_t *self, canvas_t *canvas, size_t x, size_t y) {
    if (self->step_button_is_pressed) {
        canvas_draw_image_button(
            canvas, x, y, "images/step-button-down-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click_step_button);
    } else {
        canvas_draw_image_button(
            canvas, x, y, "images/step-button-up-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click_step_button);
    }
}

static void
on_click_run_button(debug_t *self, canvas_t *canvas, uint8_t button, bool is_release) {
    (void) canvas;

    if (button == 1) {
        if (is_release) {
            self->run_button_is_pressed = false;
            self->run_toggle = !self->run_toggle;
        } else {
            self->run_button_is_pressed = true;
        }
    }
}

static void
draw_run_button(debug_t *self, canvas_t *canvas, size_t x, size_t y) {
    if (self->run_button_is_pressed || self->run_toggle) {
        canvas_draw_image_button(
            canvas, x, y, "images/run-button-down-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click_run_button);
    } else {
        canvas_draw_image_button(
            canvas, x, y, "images/run-button-up-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click_run_button);
    }
}

static void
on_click_end_button(debug_t *self, canvas_t *canvas, uint8_t button, bool is_release) {
    (void) canvas;

    if (button == 1) {
        if (is_release) {
            self->end_button_is_pressed = false;
            worker_net_run(self->worker);
            debug_update(self);
        } else {
            self->end_button_is_pressed = true;
        }
    }
}

static void
draw_end_button(debug_t *self, canvas_t *canvas, size_t x, size_t y) {
    if (self->end_button_is_pressed) {
        canvas_draw_image_button(
            canvas, x, y, "images/end-button-down-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click_end_button);
    } else {
        canvas_draw_image_button(
            canvas, x, y, "images/end-button-up-03x03.chr", TR_AP_BLENDING,
            (on_click_fn_t *) on_click_end_button);
    }
}

void
draw_toolbar(debug_t *self, canvas_t *canvas) {
    draw_step_button(
        self, canvas,
        self->canvas->width - 13 * TILE,
        self->canvas->height - 5 * TILE);

    draw_run_button(
        self, canvas,
        self->canvas->width - 9 * TILE,
        self->canvas->height - 5 * TILE);

    draw_end_button(
        self, canvas,
        self->canvas->width - 5 * TILE,
        self->canvas->height - 5 * TILE);
}
