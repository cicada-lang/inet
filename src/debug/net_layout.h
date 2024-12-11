#pragma once

struct net_layout_t {
    size_t x, y;
    size_t width, height;
    wire_t *root;
    list_t *node_layout_list;
};

net_layout_t *net_layout_new(size_t x, size_t y, size_t width, size_t height);
void net_layout_destroy(net_layout_t **self_pointer);

void net_layout_update(net_layout_t *self);
