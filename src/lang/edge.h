#pragma once

edge_t *edge_new(void);
void edge_destroy(edge_t **self_pointer);
port_t *edge_first_port(edge_t *self);
port_t *edge_second_port(edge_t *self);
