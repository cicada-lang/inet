#pragma once

stack_t *stack_new(size_t size);

size_t stack_size(const stack_t *self);
size_t stack_length(const stack_t *self);
bool stack_is_empty(const stack_t *self);
