#pragma once

// file store with cache

store_t *store_new(const char *base);
void store_destroy(store_t **self_pointer);

const char *store_base(store_t *self);
void store_purge_cache(store_t *self);
size_t store_cache_size(store_t *self);

uint8_t *store_get_fresh(store_t *self, const char* path);

uint8_t *store_get(store_t *self, const char* path);
bool store_has(store_t *self, const char* path);
