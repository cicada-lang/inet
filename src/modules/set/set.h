#pragma once

set_t *set_new(void);
void set_destroy(set_t **self_pointer);

void set_set_destroy_fn(set_t *self, destroy_fn_t *destroy_fn);
void set_set_equal_fn(set_t *self, equal_fn_t *equal_fn);

set_t *set_new_with(destroy_fn_t *destroy_fn);

size_t set_length(const set_t *self);
