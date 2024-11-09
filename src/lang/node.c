#include "index.h"

struct node_t {
    const node_spec_t *spec;
    node_id_t id;
    port_t **port_array;
};

// TODO The following function is not thread safe.
static
node_id_t
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
    size_t arity = node_spec_arity(spec);
    self->port_array = allocate_pointer_array(arity);
    return self;
}

void
node_destroy(node_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_t *self = *self_pointer;
        size_t arity = node_spec_arity(self->spec);
        for (size_t i = 0; i < arity; i++) {
            port_t *port = self->port_array[i];
            if (port) {
                // port_destroy(&port_spec);
            }
        }

        free(self->port_array);
        free(self);
        *self_pointer = NULL;
    }
}
