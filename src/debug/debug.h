#pragma once

struct debug_t {
    worker_t *worker;
    canvas_t *canvas;
};

debug_t *debug_new(worker_t *worker);
