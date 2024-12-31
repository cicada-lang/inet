#pragma once

set_t *set_new(void);
void set_destroy(set_t **self_pointer);

size_t set_length(const set_t *self);
