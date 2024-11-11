#pragma once

struct program_spec_t {
    spec_tag_t tag;
    char *name;
    program_t *program;
};

program_spec_t *program_spec_new(const char *name, program_t *program);
void program_spec_destroy(program_spec_t **self_pointer);

program_spec_t *program_spec_cast(spec_t *spec);
