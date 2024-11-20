#include "index.h"

node_t *
node_new(const node_spec_t *spec, node_id_t id) {
    node_t *self = allocate(sizeof(node_t));
    self->spec = spec;
    self->id = id;
    self->wires = allocate_pointers(spec->arity);
    return self;
}

void
node_destroy(node_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_t *self = *self_pointer;
        free(self->wires);
        // Does NOT own wires in `wires`.
        free(self);
        *self_pointer = NULL;
    }
}
