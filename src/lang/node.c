#include "index.h"

static node_id_t node_gen_id(void);

node_t *
node_new(const node_spec_t *spec) {
    node_t *self = allocate(sizeof(node_t));
    self->spec = spec;
    self->id = node_gen_id();
    self->port_array = allocate_pointer_array(spec->arity);
    return self;
}

// TODO The following function is not thread safe.
node_id_t
node_gen_id(void) {
    static node_id_t id = 0;
    id++;
    return id;
}

void
node_destroy(node_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_t *self = *self_pointer;
        free(self->port_array);
        free(self);
        *self_pointer = NULL;
    }
}
