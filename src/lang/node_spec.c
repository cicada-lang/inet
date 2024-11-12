#include "index.h"

port_spec_t *
port_spec_new(const char *name, bool is_principal) {
    port_spec_t *self = allocate(sizeof(port_spec_t));
    self->name = string_dup(name);
    self->is_principal = is_principal;
    return self;
}

void
port_spec_destroy(port_spec_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        port_spec_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

node_spec_t *
node_spec_new(
    const char *name,
    port_index_t input_arity,
    port_index_t output_arity
) {
    node_spec_t *self = allocate(sizeof(node_spec_t));
    self->tag = NODE_SPEC;
    self->name = string_dup(name);
    self->input_arity = input_arity;
    self->output_arity = output_arity;
    self->arity = input_arity + output_arity;
    self->port_specs = allocate_pointers(self->arity);
    return self;
}

void
node_spec_destroy(node_spec_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_spec_t *self = *self_pointer;
        for (port_index_t i = 0; i < self->arity; i++) {
            port_spec_t *port_spec = self->port_specs[i];
            if (port_spec) {
                port_spec_destroy(&port_spec);
            }
        }

        free(self->port_specs);
        free(self);
        *self_pointer = NULL;
    }
}

const node_spec_t *
node_spec_cast(const spec_t *spec) {
    assert(spec);
    assert(spec->tag == NODE_SPEC);
    return (node_spec_t *)spec;
}

port_index_t
node_spec_find_port_index(
    const node_spec_t *node_spec,
    const char *port_name
) {
    for (port_index_t i = 0; i < node_spec->arity; i++) {
        port_spec_t *port_spec = node_spec->port_specs[i];
        if (string_equal(port_spec->name, port_name))
            return i;
    }

    printf("[node_spec_find_port_index] fail to find index of node_name: %s, port_name: %s\n",
           node_spec->name,
           port_name);

    assert(false);
}
