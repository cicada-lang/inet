#include "index.h"

struct program_spec_t {
    spec_tag_t tag;
    char *name;
    program_t *program;
};

program_spec_t *
program_spec_new(const char *name, program_t *program) {
    program_spec_t *self = allocate(sizeof(program_spec_t));
    self->tag = PROGRAM_SPEC;
    self->name = string_dup(name);
    self->program = program;
    return self;
}
