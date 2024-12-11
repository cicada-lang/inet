#pragma once

stack_t *stack_new(void);
void stack_purge(stack_t *self);
void stack_destroy(stack_t **self_pointer);

void stack_set_destroy_fn(stack_t *self, destroy_t *destroy);
stack_t *stack_new_with(destroy_t *destroy);

size_t stack_length(const stack_t *self);
bool stack_is_empty(const stack_t *self);

void *stack_top(stack_t *self);
void *stack_pop(stack_t *self);
void stack_push(stack_t *self, void *item);

void *stack_get(stack_t *self, size_t index);
void *stack_pick(stack_t *self, size_t index);
