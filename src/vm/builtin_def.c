#include "index.h"

builtin_def_t *
builtin_def_new(const char *name, builtin_fn_t *builtin_fn) {
    builtin_def_t *self = new(builtin_def_t);
    self->kind = BUILTIN_DEF;
    self->name = string_copy(name);
    self->builtin_fn = builtin_fn;
    return self;
}

void
builtin_def_destroy(builtin_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        builtin_def_t *self = *self_pointer;
        string_destroy(&self->name);
        free(self);
        *self_pointer = NULL;
    }
}

const builtin_def_t *
builtin_def_cast(const def_t *def) {
    assert(def);
    assert(def->kind == BUILTIN_DEF);
    return (builtin_def_t *)def;
}
