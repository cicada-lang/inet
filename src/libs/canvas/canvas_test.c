#include "index.h"

void
canvas_test(void) {
    printf("<canvas_test>\n");

    canvas_t *canvas = canvas_new(3 * TILE, 3 * TILE, 10);
    canvas->title = "hello canvas";

    // {
    //     for (size_t i = 0; i < 8; i++)
    //         canvas_draw_pixel(canvas, i, i, canvas->palette[SL_COLOR]);
    //     canvas_open(canvas);
    // }

    // {
    //     canvas_fill_bottom_left(canvas, TILE, 2 * TILE, canvas->palette[SL_COLOR]);
    //     canvas_open(canvas);
    // }

    // {
    //     canvas_fill_top_right(canvas, TILE, 2 * TILE, canvas->palette[SL_COLOR]);
    //     canvas_open(canvas);
    // }

    // {
    //     canvas_fill_top_left(canvas, TILE, 2 * TILE, canvas->palette[SL_COLOR]);
    //     canvas_open(canvas);
    // }

    canvas_destroy(&canvas);

    printf("</canvas_test>\n");
}
