#pragma once

hash_t *hash_new(void);
void hash_purge(hash_t *self);
void hash_destroy(hash_t **self_pointer);

void hash_set_hash_fn(hash_t *self, hash_fn_t *hash_fn);
void hash_set_destroy_fn(hash_t *self, destroy_fn_t *destroy_fn);
void hash_set_key_destroy_fn(hash_t *self, destroy_fn_t *key_destroy_fn);
void hash_set_key_equal_fn(hash_t *self, equal_fn_t *key_equal_fn);

hash_t *hash_new_of_string_key(void);

size_t hash_length(const hash_t *self);

bool hash_has(hash_t *self, const void *key);
void *hash_get(hash_t *self, const void *key);
bool hash_set(hash_t *self, void *key, void *value);
void hash_put(hash_t *self, void *key, void *value);
bool hash_delete(hash_t *self, const void *key);

void *hash_first(hash_t *self);
void *hash_next(hash_t *self);
void *hash_cursor(hash_t *self);

list_t *hash_value_list(hash_t *self);

void hash_report(const hash_t *self);
