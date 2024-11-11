#pragma once

// `port_t` does NOT own `node` and `opposite_port`.

struct port_t {
    node_t *node;
    port_index_t index;
    port_t *opposite_port;
};

port_t *port_new(void);
void port_destroy(port_t **self_pointer);

bool port_is_principal(port_t *self);
const char *port_name(const port_t *self);

void port_free_from_node(port_t *self);

void port_print(const port_t *self);
