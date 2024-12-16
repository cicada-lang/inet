#pragma once

struct node_model_t {
    const node_t *node;
    size_t x, y;
    vec2_t force;
};

node_model_t *node_model_new(const node_t *node, size_t x, size_t y);
void node_model_destroy(node_model_t **self_pointer);

void node_model_apply_force(node_model_t *self, double cooling);
