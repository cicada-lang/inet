#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new();
    canvas->window_name = "hello world";
    canvas->width = 64 * 16;
    canvas->height = 40 * 16;
    canvas->padding = 4;

    canvas_open(canvas);

    printf("</canvas_test>\n");
}
