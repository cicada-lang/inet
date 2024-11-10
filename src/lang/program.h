#pragma once

program_t *program_new(void);
void program_destroy(program_t **self_pointer);

size_t program_length(const program_t *self);
void program_add_op(program_t *self, op_t *op);
