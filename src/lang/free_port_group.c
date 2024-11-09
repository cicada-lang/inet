#include "index.h"

// A `port_t` is a free port
// if it is not linked to a node
// and it's `index` is -1.

struct free_port_group_t {
    const node_spec_t *node_spec;
    port_t **port_array;
};

free_port_group_t *
free_port_group_new(const node_spec_t *node_spec) {
    free_port_group_t *self = allocate(sizeof(free_port_group_t));
    self->node_spec = node_spec;
    size_t arity = node_spec_arity(node_spec);
    self->port_array = allocate_pointer_array(arity);
    return self;
}
