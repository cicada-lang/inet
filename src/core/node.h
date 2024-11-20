#pragma once

struct node_t {
    const node_spec_t *spec;
    node_id_t id;
    wire_t **wires;
};

node_t *node_new(const node_spec_t *spec, node_id_t id);
void node_destroy(node_t **self_pointer);
