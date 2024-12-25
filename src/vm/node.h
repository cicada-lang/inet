#pragma once

struct node_t {
    const node_spec_t *spec;
    size_t id;
    wire_t **wires;
};

node_t *node_new(const node_spec_t *spec, size_t id);
void node_destroy(node_t **self_pointer);

void node_print(const node_t *self, file_t *file);
