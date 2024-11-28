#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(10, 10, 30);
    canvas_window_t *window = canvas_window_new(canvas);
    window->window_name = "hello canvas";
    canvas_window_open(window);

    canvas_window_destroy(&window);
    canvas_destroy(&canvas);

    printf("</canvas_test>\n");
}
