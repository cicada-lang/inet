#include "index.h"

#define WIDTH (400 * TILE)
#define HEIGHT (300 * TILE)
#define SCALE 2

debug_t *
debug_new(worker_t *worker) {
    debug_t *self = new(debug_t);
    self->worker = worker;

    canvas_t *canvas = canvas_new(WIDTH, HEIGHT, SCALE);
    canvas->state = self;
    canvas->title = "inet debug";
    self->canvas = canvas;

    return self;
}
