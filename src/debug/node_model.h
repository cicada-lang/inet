#pragma once

struct node_model_t {
    const node_t *node;
    vec2_t position;
    vec2_t velocity;
    vec2_t force;
};

node_model_t *node_model_new(const node_t *node, vec2_t position);
void node_model_destroy(node_model_t **self_pointer);
