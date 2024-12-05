#pragma once

// a dist is a string to pointer kv-map.

dict_t *dict_new(void);
void dict_purge(dict_t *self);
void dict_destroy(dict_t **self_pointer);
void dict_set_destructor(dict_t *self, destructor_t *destructor);
dict_t *dict_new_with(destructor_t *destructor);

size_t dict_length(dict_t *self);
void dict_set(dict_t *self, const char *key, void *item);
void *dict_get(dict_t *self, const char *key);
void *dict_get_or_fail(dict_t *self, const char *key);
bool dict_has(dict_t *self, const char *key);
