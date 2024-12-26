#pragma once

#define PROGRAM_DEF ((uint8_t) 1)

struct program_def_t {
    def_kind_t kind;
    char *name;
    program_t *program;
};

program_def_t *program_def_new(const char *name, program_t *program);
void program_def_destroy(program_def_t **self_pointer);
