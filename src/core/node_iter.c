#include "index.h"

struct node_iter_t {
    node_t *root;
    list_t *occurred_node_list;
    list_t *remaining_node_list;
};

node_iter_t *
node_iter_new(node_t *root) {
    node_iter_t *self = new(node_iter_t);
    self->root = root;
    self->occurred_node_list = list_new();
    self->remaining_node_list = list_new();
    return self;
}

void
node_iter_destroy(node_iter_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_iter_t *self = *self_pointer;
        list_destroy(&self->occurred_node_list);
        list_destroy(&self->remaining_node_list);
        free(self);
        *self_pointer = NULL;
    }
}
