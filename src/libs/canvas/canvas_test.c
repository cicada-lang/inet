#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(10, 10);
    canvas_window_t *canvas_window = canvas_window_new(canvas, 100);
    canvas_window->title = "hello canvas";

    canvas_draw_pixel(canvas, 0, 0, 0xffff0000);
    canvas_draw_pixel(canvas, 1, 1, 0xffff0000);
    canvas_draw_pixel(canvas, 2, 2, 0xffff0000);

    canvas_draw_pixel(canvas, 4, 4, 0xffff0000);
    canvas_draw_pixel(canvas, 5, 5, 0xffff0000);

    canvas_draw_pixel(canvas, 7, 7, 0xffff0000);
    canvas_draw_pixel(canvas, 8, 8, 0xffff0000);
    canvas_draw_pixel(canvas, 9, 9, 0xffff0000);

    canvas_window_open(canvas_window);

    canvas_window_destroy(&canvas_window);
    canvas_destroy(&canvas);

    printf("</canvas_test>\n");
}
