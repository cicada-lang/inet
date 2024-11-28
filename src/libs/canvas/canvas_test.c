#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(10, 10);
    canvas_window_t *window = canvas_window_new(canvas, 100);
    window->title = "hello canvas";

    canvas_put_pixel(canvas, 0, 0, 0xffff0000);
    canvas_put_pixel(canvas, 1, 1, 0xffff0000);
    canvas_put_pixel(canvas, 2, 2, 0xffff0000);

    canvas_put_pixel(canvas, 4, 4, 0xffff0000);
    canvas_put_pixel(canvas, 5, 5, 0xffff0000);

    canvas_put_pixel(canvas, 7, 7, 0xffff0000);
    canvas_put_pixel(canvas, 8, 8, 0xffff0000);
    canvas_put_pixel(canvas, 9, 9, 0xffff0000);

    canvas_window_open(window);

    canvas_window_destroy(&window);
    canvas_destroy(&canvas);

    printf("</canvas_test>\n");
}
