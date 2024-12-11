#pragma once

struct net_layout_t {
    size_t x, y;
    size_t width, height;

    wire_t *root;
    list_t *node_layout_list;

    uint32_t evolving_step;
    uint32_t max_evolving_step;
    double cooling_factor;
};

net_layout_t *net_layout_new(size_t x, size_t y, size_t width, size_t height);
void net_layout_destroy(net_layout_t **self_pointer);

node_layout_t *net_layout_find_node_layout(const net_layout_t *self, const node_t *node);

void net_layout_update(net_layout_t *self);

void net_layout_evolve(net_layout_t *self);
