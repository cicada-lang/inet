#include "index.h"

program_def_t *
program_def_new(const char *name, program_t *program) {
    program_def_t *self = new(program_def_t);
    self->kind = PROGRAM_DEF;
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
