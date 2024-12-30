#include "index.h"
#include "hash_primes.h"

#define INDEX_REHASH_PERCENTAGE 50
#define LENGTH_REHASH_PERCENTAGE 75

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
    void *cursor_key;

    hash_fn_t *hash_fn;
    destroy_fn_t *destroy_fn;
    destroy_fn_t *key_destroy_fn;
    equal_fn_t *key_equal_fn;
};

static size_t
hash_key_index(hash_t *self, const void *key) {
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

// reused by `hash_purge` to shrink table.
static void
hash_init(hash_t *self) {
    self->prime_index = 0;
    self->used_indexes_size = 0;
    self->length = 0;
    size_t limit = hash_primes[self->prime_index];
    self->entries = allocate_pointers(limit);
    self->cursor_index = 0;
    self->cursor_entry = NULL;
}

hash_t *
hash_new(void) {
    hash_t *self = new(hash_t);
    hash_init(self);
    return self;
}

void
hash_set_hash_fn(hash_t *self, hash_fn_t *hash_fn) {
    self->hash_fn = hash_fn;
}

void
hash_set_destroy_fn(hash_t *self, destroy_fn_t *destroy_fn) {
    self->destroy_fn = destroy_fn;
}

void
hash_set_key_destroy_fn(hash_t *self, destroy_fn_t *key_destroy_fn) {
    self->key_destroy_fn = key_destroy_fn;
}

void
hash_set_key_equal_fn(hash_t *self, equal_fn_t *key_equal_fn) {
    self->key_equal_fn = key_equal_fn;
}

hash_t *
hash_new_of_string_key(void) {
    hash_t* self = hash_new();
    hash_set_key_destroy_fn(self, (destroy_fn_t *) string_destroy);
    hash_set_key_equal_fn(self, (equal_fn_t *) string_equal);
    hash_set_hash_fn(self, (hash_fn_t *) string_bernstein_hash);    
    return self;
}

static void hash_delete_entry(hash_t *self, entry_t *entry);

static void
hash_purge_without_shrink(hash_t *self) {
    size_t limit = hash_primes[self->prime_index];
    for (size_t index = 0; index < limit; index++) {
        // destroy all entries in this hash bucket.
        entry_t *entry = self->entries[index];
        while (entry) {
            entry_t *next = entry->next;
            hash_delete_entry(self, entry);
            entry = next;
        }

        self->entries[index] = NULL;
    }
}

void
hash_destroy(hash_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        hash_t *self = *self_pointer;
        hash_purge_without_shrink(self);
        free(self->entries);
        free(self);
        *self_pointer = NULL;
    }
}

void
hash_purge(hash_t *self) {
    hash_purge_without_shrink(self);
    free(self->entries);
    hash_init(self);
}

size_t
hash_length(const hash_t *self) {
    return self->length;
}

static void
hash_rehash(hash_t *self, size_t new_prime_index) {
    assert(self);
    assert(new_prime_index < sizeof(hash_primes));

    size_t old_limit = hash_primes[self->prime_index];
    size_t new_limit = hash_primes[new_prime_index];
    entry_t **new_entries = allocate_pointers(new_limit);

    // to debug performance:
    // {
    //     hash_report(self);
    // }

    self->prime_index = new_prime_index;
    self->used_indexes_size = 0;

    for (size_t index = 0; index < old_limit; index++) {
        entry_t *entry = self->entries[index];
        while (entry) {
            entry_t *next = entry->next;
            size_t new_index = hash_key_index(self, entry->key);
            entry->index = new_index;
            entry_t *top_entry = new_entries[new_index];
            if (!top_entry)
                self->used_indexes_size++;

            entry->next = top_entry;
            new_entries[new_index] = entry;
            entry = next;
        }
    }

    free(self->entries);
    self->entries = new_entries;
}

static bool
hash_key_equal(hash_t *self, const void *key1, const void *key2) {
    if (!self->key_equal_fn)
        return key1 == key2;

    return self->key_equal_fn(key1, key2);
}

static entry_t *
hash_get_entry(hash_t *self, const void *key) {
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

bool
hash_has(hash_t *self, const void *key) {
    entry_t *entry = hash_get_entry(self, key);
    return entry != NULL;
}

void *
hash_get(hash_t *self, const void *key) {
    entry_t *entry = hash_get_entry(self, key);
    if (!entry) return NULL;

    return entry->value;
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
        self->used_indexes_size++;
        self->length++;
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
    self->length++;
    return true;
}

static void
hash_delete_entry(hash_t *self, entry_t *entry) {
    // find previous entry since it's a singly-linked list.
    entry_t **entry_pointer = &(self->entries[entry->index]);
    entry_t *cursor_entry = self->entries[entry->index];
    while (cursor_entry) {
        if (cursor_entry == entry) break;
        entry_pointer = &(cursor_entry->next);
        cursor_entry = cursor_entry->next;
    }

    // entry must in the table.
    assert(cursor_entry);
    *entry_pointer = entry->next;
    self->length--;
    if (entry_pointer == &(self->entries[entry->index]))
        self->used_indexes_size--;

    if (self->destroy_fn)
        self->destroy_fn(&entry->value);
    if (self->key_destroy_fn)
        self->key_destroy_fn(&entry->key);
    free(entry);
}

void
hash_delete(hash_t *self, const void *key) {
    entry_t *entry = hash_get_entry(self, key);
    if (!entry) return;

    hash_delete_entry(self, entry);
}

static bool
hash_is_overload(hash_t *self) {
    size_t limit = hash_primes[self->prime_index];
    return ((self->length >= limit * LENGTH_REHASH_PERCENTAGE / 100) ||
            (self->used_indexes_size >= limit * INDEX_REHASH_PERCENTAGE / 100));
}

bool
hash_set(hash_t *self, void *key, void *value) {
    if (hash_is_overload(self))
        hash_rehash(self, self->prime_index + 1);

    return hash_set_entry_if_not_exists(self, key, value);
}

void
hash_put(hash_t *self, void *key, void *value) {
    entry_t *entry = hash_get_entry(self, key);
    if (!entry) {
        assert(hash_set(self, key, value));
        return;
    }

    if (self->destroy_fn)
        self->destroy_fn(&entry->value);
    entry->value = value;
}

void *
hash_first(hash_t *self) {
    assert(self);
    self->cursor_index = 0;
    self->cursor_entry = self->entries[self->cursor_index];
    return hash_next(self);
}

void *
hash_cursor(hash_t *self) {
    return self->cursor_key;
}

void *
hash_next(hash_t *self) {
    assert (self);
    // Scan forward from cursor until we find an non empty bucket
    size_t limit = hash_primes[self->prime_index];
    while (!self->cursor_entry) {
        if (self->cursor_index < limit - 1)
            self->cursor_index++;
        else
            return NULL;

        self->cursor_entry = self->entries[self->cursor_index];
    }

    // We have an entry, so return it, and bump past it
    assert(self->cursor_entry);
    entry_t *entry = self->cursor_entry;
    self->cursor_key = entry->key;
    self->cursor_entry = entry->next;
    return entry->value;
}

list_t *
hash_value_list(hash_t *self) {
    list_t *list = list_new();
    void *value = hash_first(self);
    while (value) {
        list_push(list, value);
        value = hash_next(self);
    }

    return list;
}

void
hash_report(const hash_t *self) {
    size_t limit = hash_primes[self->prime_index];
    size_t length_percentage = self->length * 100 / limit;
    size_t index_percentage = self->used_indexes_size * 100 / limit;

    printf("[hash_report] length percentage : %lu\n", length_percentage);
    printf("[hash_report] index  percentage : %lu\n", index_percentage);
    printf("[hash_report] prime index : %lu\n", self->prime_index);
    printf("[hash_report] prime       : %lu\n", limit);
    printf("[hash_report] used idx: %lu\n", self->used_indexes_size);
    printf("[hash_report] length  : %lu\n", self->length);

    size_t max_chain = 0;
    for (size_t i = 0; i < limit; i++) {
        entry_t *entry = self->entries[i];
        size_t length = 0;
        while (entry) {
            entry = entry->next;
            length++;
        }

        max_chain = uint_max(length, max_chain);
    }

    printf("[hash_report] max_chain  : %lu\n", max_chain);

    printf("\n");
}
