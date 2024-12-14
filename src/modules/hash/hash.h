#pragma once

hash_t *hash_new(void);
void hash_purge(hash_t *self);
void hash_destroy(hash_t **self_pointer);

void *hash_get(hash_t *self, void *key);
void hash_set(hash_t *self, void *key, void *value);
void hash_put(hash_t *self, void *key, void *value);
