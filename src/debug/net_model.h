#pragma once

struct net_model_t {
    size_t x, y;
    size_t width, height;

    wire_t *root;
    hash_t *node_model_hash;

    uint32_t evolving_step;
    uint32_t max_evolving_step;
    double cooling_factor;
};

net_model_t *net_model_new(size_t x, size_t y, size_t width, size_t height);
void net_model_destroy(net_model_t **self_pointer);

node_model_t *net_model_find_node_model(const net_model_t *self, const node_t *node);

void net_model_update(net_model_t *self);

void net_model_evolve(net_model_t *self);
