#pragma once

program_t *program_new(void);
void program_destroy(program_t **self_pointer);

size_t program_length(const program_t *self);
void program_add_op(program_t *self, op_t *op);
void program_build(program_t *self);
op_t *program_get_op(const program_t *self, size_t index);

void program_print(const program_t *self, file_t *file);
void program_print_with_program_counter(const program_t *self, file_t *file, size_t program_counter);
