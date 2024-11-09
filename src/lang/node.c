#include "index.h"

struct node_t {
    const node_spec_t *spec;
    node_id_t id;
    port_t **port_array;
};

// TODO The following function is not thread safe.
static node_id_t
node_gen_id() {
    static node_id_t id = 0;
    id++;
    return id;
}


node_t *
node_new(const node_spec_t *spec) {
    node_t *self = allocate(sizeof(node_t));
    self->spec = spec;
    self->id = node_gen_id();
    self->port_array = allocate_pointer_array(node_spec_arity(spec));
    return self;
}
