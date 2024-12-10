#pragma once

node_iter_t *node_iter_new(node_t *root);
void node_iter_destroy(node_iter_t **self_pointer);

node_t *node_iter_start(node_iter_t *self);
node_t *node_iter_next(node_iter_t *self);
