#pragma once

array_t *array_new(size_t size);
void array_purge(array_t *self);
void array_destroy(array_t **self_pointer);

void array_set_destructor(array_t *self, destructor_t *destructor);
array_t *array_new_with(size_t size, destructor_t *destructor);

size_t array_size(const array_t *self);
size_t array_length(const array_t *self);
bool array_is_empty(const array_t *self);
bool array_is_full(const array_t *self);

void *array_top(array_t *self);
void *array_pop(array_t *self);
void array_push(array_t *self, void *item);

void *array_get(array_t *self, size_t index);
void *array_pick(array_t *self, size_t index);
