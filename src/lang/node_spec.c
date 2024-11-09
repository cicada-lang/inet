#include "index.h"

struct node_spec_t {
    spec_tag_t tag;
    const char *name;
    size_t input_arity;
    size_t output_arity;
    port_spec_t *port_spec_array;
};

node_spec_t *
node_spec_new(
    const char *name,
    size_t input_arity,
    size_t output_arity
) {
    node_spec_t *self = allocate(sizeof(node_spec_t));
    self->tag = NODE_SPEC;
    self->name = name;
    self->input_arity = input_arity;
    self->output_arity = output_arity;
    size_t arity = input_arity + output_arity;
    self->port_spec_array = allocate_array(arity, sizeof(port_spec_t *));
    return self;
}
