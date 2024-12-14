#include "index.h"

struct store_t {
    const char *base;
    dict_t *cached_blob_dict;
};

store_t *
store_new(const char *base) {
    store_t *self = new(store_t);
    self->base = base;
    self->cached_blob_dict = dict_new_with((destroy_fn_t *) blob_destroy);
    return self;
}

void
store_destroy(store_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        store_t *self = *self_pointer;
        dict_destroy(&self->cached_blob_dict);
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
    dict_purge(self->cached_blob_dict);
}

size_t
store_cache_size(store_t *self) {
    return dict_length(self->cached_blob_dict);
}

blob_t *
store_get_cache(store_t *self, const char* path) {
    return dict_get(self->cached_blob_dict, path);
}

void
store_set_cache(store_t *self, const char* path, blob_t *blob) {
    dict_set(self->cached_blob_dict, path, blob);
}

blob_t *
store_get_fresh(store_t *self, const char* path) {
    char *normalized_path = string_append("/", path);
    char *file_name = string_append(self->base, normalized_path);

    if (!file_exists(file_name)) {
        return NULL;
    }

    file_t *file = fopen(file_name, "rb");
    blob_t *blob = file_read_blob(file);

    free(normalized_path);
    free(file_name);
    fclose(file);

    return blob;
}

blob_t *
store_get(store_t *self, const char* path) {
    blob_t *cached_blob = store_get_cache(self, path);
    if (cached_blob) {
        return cached_blob;
    }

    blob_t *fresh_blob = store_get_fresh(self, path);
    if (fresh_blob) {
        store_set_cache(self, path, fresh_blob);
    }

    return fresh_blob;
}

bool
store_has(store_t *self, const char* path) {
    blob_t *blob = store_get(self, path);
    if (blob) {
        return true;
    } else {
        return false;
    }
}
