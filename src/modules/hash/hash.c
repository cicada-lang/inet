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

static size_t
hash_key_index(hash_t *self, void *key) {
    size_t base = self->hash_fn ? self->hash_fn(key) : (size_t) key;
    size_t limit = hash_primes[self->prime_index];
    size_t index = base % limit;
    return index;
}

static entry_t *
hash_new_entry(hash_t *self, void *key, void *value) {
    entry_t *entry = new(entry_t);
    entry->index = hash_key_index(self, key);
    entry->key = key;
    entry->value = value;
    return entry;
}

static void
hash_destroy_entry(hash_t *self, entry_t **entry_pointer) {
    assert(entry_pointer);
    if (*entry_pointer) {
        entry_t *entry = *entry_pointer;
        if (self->destroy_fn)
            self->destroy_fn(&entry->value);
        if (self->key_destroy_fn)
            self->key_destroy_fn(&entry->key);
        hash_destroy_entry(self, &entry->next);
        free(entry);
        *entry_pointer = NULL;
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
    if (!self->key_equal_fn)
        return key1 == key2;

    return self->key_equal_fn(key1, key2);
}

static entry_t *
hash_get_entry(hash_t *self, void *key) {
    size_t index = hash_key_index(self, key);
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

// no rehash here.
// if not exists return true,
// if exists return false.
static bool
hash_set_entry_if_not_exists(hash_t *self, void *key, void *value) {
    size_t index = hash_key_index(self, key);
    entry_t *entry = self->entries[index];
    if (!entry) {
        entry_t *new_entry = hash_new_entry(self, key, value);
        self->entries[index] = new_entry;
        return true;
    }

    while (entry) {
        if (hash_key_equal(self, entry->key, key))
            return false;

        entry = entry->next;
    }

    entry_t *new_entry = hash_new_entry(self, key, value);
    entry_t *top_entry = self->entries[index];
    self->entries[index] = new_entry;
    new_entry->next = top_entry;
    return true;
}

void todo(void) {
    (void) hash_set_entry_if_not_exists;
    (void) hash_new_entry;
    (void) hash_destroy_entry;
}
