#pragma once

// file store with cache

store_t *store_new(const char *base);
void store_destroy(store_t **self_pointer);

const char *store_base(store_t *self);
void store_purge_cache(store_t *self);
size_t store_cache_length(store_t *self);

blob_t *store_get_cache(store_t *self, const char* path);
void store_set_cache(store_t *self, const char* path, blob_t *blob);

blob_t *store_get_fresh(store_t *self, const char* path);

blob_t *store_get(store_t *self, const char* path);
bool store_has(store_t *self, const char* path);
