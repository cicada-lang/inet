#include "index.h"

#define INDEX_REHASH_PERCENTAGE 60
#define LENGHT_REHASH_PERCENTAGE 75

typedef struct entry_t entry_t;

struct entry_t {
    size_t index;
    void *key;
    void *value;
    entry_t *next;
};

struct hash_t {
    size_t prime_index;
    size_t used_indexes_size;
    size_t length;
    entry_t **entries;

    size_t cursor_index;
    entry_t *cursor_entry;

    hash_fn_t *hash_fn;
    destroy_fn_t *destroy_fn;
    destroy_fn_t *key_destroy_fn;
    equal_fn_t *key_equal_fn;
};

static entry_t *
entry_new(size_t index, void *key, void *value) {
    entry_t *self = new(entry_t);
    self->index = index;
    self->key = key;
    self->value = value;
    return self;
}

static void
hash_entry_destroy(hash_t *hash, entry_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        entry_t *self = *self_pointer;
        if (hash->destroy_fn)
            hash->destroy_fn(&self->value);
        if (hash->key_destroy_fn)
            hash->key_destroy_fn(&self->key);
        hash_entry_destroy(hash, &self->next);
        free(self);
        *self_pointer = NULL;
    }
}

hash_t *
hash_new(void) {
    hash_t *self = new(hash_t);
    self->prime_index = 0;
    self->used_indexes_size = 0;
    self->length = 0;
    size_t limit = hash_primes[self->prime_index];
    self->entries = allocate_pointers(limit);
    self->cursor_index = 0;
    self->cursor_entry = NULL;
    return self;
}

static bool
hash_key_equal(hash_t *self, void *key1, void *key2) {
    (void) self;
    (void) key1;
    (void) key2;
    return true;
}

static entry_t *
hash_get_entry(hash_t *self, void *key) {
    size_t base = self->hash_fn ? self->hash_fn(key) : (size_t) key;
    size_t limit = hash_primes[self->prime_index];
    size_t index = base % limit;
    entry_t *entry = self->entries[index];
    if (!entry) return NULL;

    while (entry) {
        if (hash_key_equal(self, entry->key, key))
            return entry;
        entry = entry->next;
    }

    return NULL;
}

void *
hash_get(hash_t *self, void *key) {
    entry_t *entry = hash_get_entry(self, key);
    if (!entry) return NULL;

    return entry;
}

void todo(void) {
    (void) entry_new;
    (void) hash_entry_destroy;
}
