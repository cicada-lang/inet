#pragma once

struct node_physics_system_t {
    size_t x, y;
    size_t width, height;

    wire_t *root; // to query relation between nodes.
    hash_t *node_model_hash;

    uint32_t evolving_step;
    uint32_t max_evolving_step;
    double cooling_factor;
};

node_physics_system_t *node_physics_system_new(size_t x, size_t y, size_t width, size_t height);
void node_physics_system_destroy(node_physics_system_t **self_pointer);

void node_physics_system_add_node_models(node_physics_system_t *self, hash_t *node_hash, hash_t *node_model_hash);
void node_physics_system_evolve(node_physics_system_t *self, hash_t *node_model_hash);
