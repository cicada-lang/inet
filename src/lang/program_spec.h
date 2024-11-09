#pragma once

program_spec_t *program_spec_new(const char *name, program_t *program);
void program_spec_destroy(program_spec_t **self_pointer);

const char *program_spec_name(program_spec_t *self);
