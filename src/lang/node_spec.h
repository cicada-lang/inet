#pragma once

node_spec_t *node_spec_new(
    const char *name,
    size_t input_arity,
    size_t output_arity);
void node_spec_destroy(node_spec_t **self_pointer);

const char *node_spec_name(node_spec_t *self);
size_t node_spec_input_arity(node_spec_t *self);
size_t node_spec_output_arity(node_spec_t *self);
size_t node_spec_arity(node_spec_t *self);

void node_spec_set_port_spec(
    node_spec_t *self,
    size_t index,
    port_spec_t *port_spec);
const port_spec_t *node_spec_get_port_spec(
    node_spec_t *self,
    size_t index);
