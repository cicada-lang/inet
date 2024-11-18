#include "index.h"

builtin_spec_t *
builtin_spec_new(const char *name, builtin_t *builtin) {
    builtin_spec_t *self = allocate(sizeof(builtin_spec_t));
    self->tag = BUILTIN_SPEC;
    self->name = string_dup(name);
    self->builtin = builtin;
    return self;
}

void
builtin_spec_destroy(builtin_spec_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        builtin_spec_t *self = *self_pointer;
        string_destroy(&self->name);
        free(self);
        *self_pointer = NULL;
    }
}

const builtin_spec_t *
builtin_spec_cast(const spec_t *spec) {
    assert(spec);
    assert(spec->tag == BUILTIN_SPEC);
    return (builtin_spec_t *)spec;
}
