#include "index.h"

net_layout_t *
net_layout_new(size_t x, size_t y, size_t width, size_t height) {
    net_layout_t *self = new(net_layout_t);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->node_layout_list =
        list_new_with((destroy_t *) node_layout_destroy);
    return self;
}

void
net_layout_destroy(net_layout_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        net_layout_t *self = *self_pointer;
        list_destroy(&self->node_layout_list);
        free(self);
        *self_pointer = NULL;
    }
}

node_layout_t *
net_layout_find_node_layout(const net_layout_t *self, const node_t *node) {
    node_layout_t *node_layout = list_start(self->node_layout_list);
    while (node_layout) {
        if (node_layout->node == node)
            return node_layout;

        node_layout = list_next(self->node_layout_list);
    }

    return NULL;
}

void
net_layout_update(net_layout_t *self) {
    if (!self->root) return;
    if (!self->root->opposite) return;
    if (!self->root->opposite->node) return;

    node_iter_t *iter = node_iter_new(self->root->opposite->node);
    list_t *new_list = list_new_with((destroy_t *) node_layout_destroy);
    node_t *node = node_iter_start(iter);
    while (node) {
        node_layout_t *found = net_layout_find_node_layout(self, node);
        if (found) {
            list_push(new_list, found);
            list_remove(self->node_layout_list, found);
        } else {
            size_t x = self->width * ((double) rand() / RAND_MAX);
            size_t y = self->height * ((double) rand() / RAND_MAX);
            node_layout_t *node_layout = node_layout_new(node, x, y);
            list_push(new_list, node_layout);
        }

        node = node_iter_next(iter);
    }
    node_iter_destroy(&iter);

    list_destroy(&self->node_layout_list);
    self->node_layout_list = new_list;
}
