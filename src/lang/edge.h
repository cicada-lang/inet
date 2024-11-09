#pragma once

// `edge_t` does NOT own `first_port` and `second_port`.

struct edge_t {
    port_t *first_port;
    port_t *second_port;
};

edge_t *edge_new(void);
void edge_destroy(edge_t **self_pointer);
