#include "index.h"

primitive_def_t *
primitive_def_new(const char *name, primitive_fn_t *primitive_fn) {
    primitive_def_t *self = new(primitive_def_t);
    self->name = string_copy(name);
    self->primitive_fn = primitive_fn;
    return self;
}

void
primitive_def_destroy(primitive_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        primitive_def_t *self = *self_pointer;
        string_destroy(&self->name);
        free(self);
        *self_pointer = NULL;
    }
}
