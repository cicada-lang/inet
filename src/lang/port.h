#pragma once

port_t *port_new(void);
void port_destroy(port_t **self_pointer);

const node_t *port_node(port_t *self);
void port_set_node(port_t *self, node_t *node);

port_index_t port_index(port_t *self);
void port_set_index(port_t *self, port_index_t index);

const port_t *port_opposite_port(port_t *self);
void port_set_opposite_port(port_t *self, const port_t *port);
