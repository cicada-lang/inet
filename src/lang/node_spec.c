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
    size_t input_arity,
    size_t output_arity
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
        for (size_t i = 0; i < self->arity; i++) {
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
