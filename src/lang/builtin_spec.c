#include "index.h"

builtin_spec_t *
builtin_spec_new(const char *name, builtin_t *builtin) {
    builtin_spec_t *self = allocate(sizeof(builtin_spec_t));
    self->tag = BUILTIN_SPEC;
    self->name = string_dup(name);
    self->builtin = builtin;
    return self;
}
