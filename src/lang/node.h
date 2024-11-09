#pragma once

// `node_t` does NOT own ports in `ports`.

struct node_t {
    const node_spec_t *spec;
    node_id_t id;
    port_t **ports;
};

node_t *node_new(const node_spec_t *spec);
void node_destroy(node_t **self_pointer);
