#include "index.h"

constant_def_t *
constant_def_new(const char *name, value_t value) {
    constant_def_t *self = new(constant_def_t);
    self->name = string_copy(name);
    self->value = value;
    return self;
}

void
constant_def_destroy(constant_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        constant_def_t *self = *self_pointer;
        string_destroy(&self->name);
        free(self);
        *self_pointer = NULL;
    }
}
