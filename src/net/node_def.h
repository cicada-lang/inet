#pragma once

struct node_def_t {
    char *name;
    port_index_t input_arity;
    port_index_t output_arity;
    port_index_t arity;
    port_def_t **port_defs;
};

node_def_t *node_def_new(
    const char *name,
    port_index_t input_arity,
    port_index_t output_arity);
void node_def_destroy(node_def_t **self_pointer);

port_index_t node_def_find_port_index(const node_def_t *node_def, const char *port_name);
