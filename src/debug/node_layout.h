#pragma once

struct node_layout_t {
    const node_t *node;
    size_t x, y;
};

node_layout_t *node_layout_new(const node_t *node);
