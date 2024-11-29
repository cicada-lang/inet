#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(0x10 * 8, 0x10 * 8);
    canvas_window_t *canvas_window = canvas_window_new(canvas, 8);
    canvas_window->title = "hello canvas";

    // file_t *file = file_open_or_fail(
    //     // "/home/xyh/projects/others/rabbits/uxn/projects/pictures/akane20x10.icn",
    //     "/home/xyh/projects/others/rabbits/uxn/projects/pictures/cibo10x10.icn",
    //     "rb");
    // uint8_t *bytes = file_read_bytes(file);
    // canvas_draw_icn(canvas, 0, 0, bytes, 0x10, 0x10);

    // canvas_window_open(canvas_window);

    canvas_window_destroy(&canvas_window);
    canvas_destroy(&canvas);

    printf("</canvas_test>\n");
}
