#include "index.h"

struct store_t {
    const char *base;
    dict_t *cache_dict;
};

store_t *
store_new(const char *base) {
    store_t *self = new(store_t);
    self->base = base;
    self->cache_dict = dict_new_with((destructor_t *) destroy);
    return self;
}

void
store_destroy(store_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        store_t *self = *self_pointer;
        dict_destroy(&self->cache_dict);
        free(self);
        *self_pointer = NULL;
    }
}

const char *
store_base(store_t *self) {
    return self->base;
}

void
store_purge_cache(store_t *self) {
    dict_purge(self->cache_dict);
}

size_t
store_cache_size(store_t *self) {
    return dict_length(self->cache_dict);
}

uint8_t *
store_get_cache(store_t *self, const char* path) {
    return dict_get(self->cache_dict, path);
}

void
store_set_cache(store_t *self, const char* path, uint8_t *bytes) {
    dict_set(self->cache_dict, path, bytes);
}

uint8_t *
store_get_fresh(store_t *self, const char* path) {
    char *normalized_path = string_append("/", path);
    char *file_name = string_append(self->base, normalized_path);

    if (!file_exists(file_name)) {
        return NULL;
    }

    file_t *file = fopen(file_name, "rb");
    uint8_t *bytes = file_read_bytes(file);

    free(normalized_path);
    free(file_name);
    fclose(file);

    return bytes;
}

uint8_t *
store_get(store_t *self, const char* path) {
    uint8_t *cached_bytes = store_get_cache(self, path);
    if (cached_bytes) {
        return cached_bytes;
    }

    uint8_t *fresh_bytes = store_get_fresh(self, path);
    if (fresh_bytes) {
        store_set_cache(self, path, fresh_bytes);
    }

    return fresh_bytes;
}

bool
store_has(store_t *self, const char* path) {
    uint8_t *bytes = store_get(self, path);
    if (bytes) {
        return true;
    } else {
        return false;
    }
}
