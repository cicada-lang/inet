#pragma once

struct debug_t {
    worker_t *worker;
    canvas_t *canvas;
    node_physics_system_t *node_physics_system;
};

debug_t *debug_new(worker_t *worker);
void debug_destroy(debug_t **self_pointer);

void debug_start(worker_t *worker);
