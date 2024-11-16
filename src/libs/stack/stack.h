#pragma once

typedef void (stack_item_destructor_t)(void **item);

stack_t *stack_new(size_t size);
void stack_purge(stack_t *self);
void stack_destroy(stack_t **self_pointer);

void stack_set_item_destructor(stack_t *self, stack_item_destructor_t *item_destructor);
size_t stack_size(const stack_t *self);
size_t stack_length(const stack_t *self);
bool stack_is_empty(const stack_t *self);

void *stack_top(stack_t *self);
void *stack_pop(stack_t *self);
void stack_push(stack_t *self, void *item);

void *stack_get(stack_t *self, size_t index);
void *stack_pick(stack_t *self, size_t index);
