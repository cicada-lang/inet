#pragma once

struct port_spec_t {
    char *name;
    bool is_principal;
};

port_spec_t *port_spec_new(const char *name, bool is_principal);
void port_spec_destroy(port_spec_t **self_pointer);

struct node_spec_t {
    spec_tag_t tag;
    char *name;
    port_index_t input_arity;
    port_index_t output_arity;
    port_index_t arity;
    port_spec_t **port_specs;
};

node_spec_t *node_spec_new(
    const char *name,
    port_index_t input_arity,
    port_index_t output_arity);
void node_spec_destroy(node_spec_t **self_pointer);

const node_spec_t *node_spec_cast(const spec_t *spec);
port_index_t node_spec_find_port_index(const node_spec_t *node_spec, const char *port_name);
