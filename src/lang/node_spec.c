#include "index.h"

struct node_spec_t {
    spec_tag_t tag;
    char *name;
    size_t input_arity;
    size_t output_arity;
    size_t arity;
    port_spec_t **port_spec_array;
};

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
    self->port_spec_array = allocate_array(self->arity, sizeof(port_spec_t *));
    return self;
}

void
node_spec_destroy(node_spec_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_spec_t *self = *self_pointer;
        for (size_t i = 0; i < self->arity; i++) {
            port_spec_t *port_spec = self->port_spec_array[i];
            if (port_spec) {
                port_spec_destroy(&port_spec);
            }
        }

        free(self->port_spec_array);
        free(self);
        *self_pointer = NULL;
    }
}

const char *
node_spec_name(node_spec_t *self) {
    return self->name;
}

size_t
node_spec_input_arity(node_spec_t *self) {
    return self->input_arity;
}

size_t
node_spec_output_arity(node_spec_t *self) {
    return self->output_arity;
}

size_t
node_spec_arity(node_spec_t *self) {
    return self->arity;
}
