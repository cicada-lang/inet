#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(64 * 8, 40 * 8);
    canvas->window_name = "hello canvas";
    canvas_open(canvas);

    printf("</canvas_test>\n");
}
