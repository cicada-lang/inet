#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new();
    canvas->window_name = "hello world";

    printf("</canvas_test>\n");
}
