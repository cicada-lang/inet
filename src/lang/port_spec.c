#include "index.h"

struct port_spec_t {
    const char *name;
    bool is_principal;
};

port_spec_t *
port_spec_new(const char *name, bool is_principal) {
    port_spec_t *self = allocate(sizeof(port_spec_t));
    self->name = name;
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
