#pragma once

stack_t *stack_new(size_t size);
void stack_purge(stack_t *self);
void stack_destroy(stack_t **self_pointer);

size_t stack_size(const stack_t *self);
size_t stack_length(const stack_t *self);
bool stack_is_empty(const stack_t *self);
