#include "index.h"

#define INDEX_REHASH_PERCENTAGE 60
#define LENGHT_REHASH_PERCENTAGE 75

typedef struct entry_t entry_t;

struct entry_t {
    hash_t *hash;
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
};

static entry_t *
entry_new(hash_t *hash, size_t index, void *key, void *value) {
    entry_t *self = new(entry_t);
    self->hash = hash;
    self->index = index;
    self->key = key;
    self->value = value;
    return self;
}

static void
entry_destroy(entry_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        entry_t *self = *self_pointer;
        if (self->hash->destroy_fn)
            self->hash->destroy_fn(&self->value);
        if (self->hash->key_destroy_fn)
            self->hash->key_destroy_fn(&self->key);
        entry_destroy(&self->next);
        free(self);
        *self_pointer = NULL;
    }
}

hash_t *
hash_new(void) {
    (void) entry_new;
    (void) entry_destroy;

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
