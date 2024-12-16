#pragma once

struct debug_t {
    worker_t *worker;

    canvas_t *canvas;
    size_t width, height, scale;
    bool step_button_is_pressed;

    hash_t *node_hash;
    hash_t *node_model_hash;
    node_physics_t *node_physics;
};

debug_t *debug_new(worker_t *worker);
void debug_destroy(debug_t **self_pointer);

void debug_start(worker_t *worker);
