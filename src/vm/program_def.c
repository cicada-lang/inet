#include "index.h"

program_def_t *
program_def_new(const char *name, program_t *program) {
    program_def_t *self = new(program_def_t);
    self->kind = PROGRAM_DEF_KIND;
    self->name = string_copy(name);
    self->program = program;
    return self;
}

void
program_def_destroy(program_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        program_def_t *self = *self_pointer;
        string_destroy(&self->name);
        program_destroy(&self->program);
        free(self);
        *self_pointer = NULL;
    }
}

const program_def_t *
program_def_cast(const def_t *def) {
    assert(def);
    assert(def->kind == PROGRAM_DEF_KIND);
    return (program_def_t *)def;
}
