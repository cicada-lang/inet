#pragma once

struct node_physics_t {
    size_t x, y, width, height; // rect within the canvas
    wire_t *root; // to query relation between nodes.
    uint32_t evolving_step;
    uint32_t max_evolving_step;
    double cooling_factor;
};

node_physics_t *node_physics_new(size_t x, size_t y, size_t width, size_t height);
void node_physics_destroy(node_physics_t **self_pointer);

void node_physics_add_more_nodes(node_physics_t *self, hash_t *node_hash, hash_t *node_model_hash);
void node_physics_evolve(node_physics_t *self, hash_t *node_model_hash);
