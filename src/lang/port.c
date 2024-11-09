#include "index.h"

port_t *
port_new(void) {
    port_t *self = allocate(sizeof(port_t));
    self->node = NULL;
    self->index = -1;
    self->opposite_port = NULL;
    return self;
}

void
port_destroy(port_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        port_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

bool
port_is_principal(port_t *self) {
    port_spec_t *port_spec = self->node->spec->port_spec_array[self->index];
    return port_spec->is_principal;
}
