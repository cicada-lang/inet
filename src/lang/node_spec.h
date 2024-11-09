#pragma once

struct node_spec_t {
    spec_tag_t tag;
    char *name;
    size_t input_arity;
    size_t output_arity;
    size_t arity;
    port_spec_t **port_spec_array;
};

node_spec_t *node_spec_new(
    const char *name,
    size_t input_arity,
    size_t output_arity);
void node_spec_destroy(node_spec_t **self_pointer);
