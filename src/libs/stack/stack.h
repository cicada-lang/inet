#pragma once

stack_t *stack_new(size_t size);
void stack_purge(stack_t *self);
void stack_destroy(stack_t **self_pointer);

void stack_set_destructor(stack_t *self, destructor_t *destructor);
stack_t *stack_new_with(size_t size, destructor_t *destructor);

size_t stack_size(const stack_t *self);
size_t stack_length(const stack_t *self);
bool stack_is_empty(const stack_t *self);

void *stack_top(stack_t *self);
void *stack_pop(stack_t *self);
void stack_push(stack_t *self, void *item);

void *stack_get(stack_t *self, size_t index);
void *stack_pick(stack_t *self, size_t index);
