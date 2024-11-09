#pragma once

port_t *port_new();
void port_destroy(port_t **self_pointer);

const node_t *port_node(port_t *self);
void port_set_node(port_t *self, node_t *node);

port_index_t port_index(port_t *self);
void port_set_index(port_t *self, port_index_t index);
