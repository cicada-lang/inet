#pragma once

node_spec_t *node_spec_new(
    const char *name,
    size_t input_arity,
    size_t output_arity);
void node_spec_destroy(node_spec_t **self_pointer);
