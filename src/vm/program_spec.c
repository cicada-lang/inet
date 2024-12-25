#include "index.h"

program_spec_t *
program_spec_new(const char *name, program_t *program) {
    program_spec_t *self = new(program_spec_t);
    self->kind = PROGRAM_SPEC;
    self->name = string_copy(name);
    self->program = program;
    return self;
}

void
program_spec_destroy(program_spec_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        program_spec_t *self = *self_pointer;
        string_destroy(&self->name);
        program_destroy(&self->program);
        free(self);
        *self_pointer = NULL;
    }
}

const program_spec_t *
program_spec_cast(const spec_t *spec) {
    assert(spec);
    assert(spec->kind == PROGRAM_SPEC);
    return (program_spec_t *)spec;
}
