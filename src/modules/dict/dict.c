#include "index.h"

struct entry_t {
    char *key;
    void *item;
};

typedef struct entry_t entry_t;

entry_t *entry_new(char *key, void *item);
void entry_destroy(entry_t **self_pointer);

entry_t *
entry_new(char *key, void *item) {
    entry_t *self = new(entry_t);
    self->key = key;
    self->item = item;
    return self;
}

void
entry_destroy(entry_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        entry_t *self = *self_pointer;
        free(self->key);
        free(self);
        *self_pointer = NULL;
    }
}

struct dict_t {
    list_t *entry_list;
    destructor_t *destructor;
};

dict_t *
dict_new(void) {
    dict_t *self = new(dict_t);
    self->entry_list = list_new_with((destructor_t *) entry_destroy);
    return self;
}

void
dict_set_destructor(dict_t *self, destructor_t *destructor) {
    self->destructor = destructor;
}

dict_t *
dict_new_with(destructor_t *destructor) {
    dict_t *self = dict_new();
    self->destructor = destructor;
    return self;
}

void
dict_purge(dict_t *self) {
    if (self->destructor) {
        entry_t *entry = list_pop(self->entry_list);
        while (entry) {
            self->destructor(&entry->item);
            entry_destroy(&entry);
            entry = list_pop(self->entry_list);
        }
    }
}

void
dict_destroy(dict_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        dict_t *self = *self_pointer;
        dict_purge(self);
        list_destroy(&self->entry_list);
        free(self);
        *self_pointer = NULL;
    }
}

size_t
dict_length(dict_t *self) {
    return list_length(self->entry_list);
}

void
dict_set(dict_t *self, const char *key, void *item) {
    entry_t *entry = list_start(self->entry_list);
    while (entry) {
        if (string_equal(entry->key, key)) {
            if (self->destructor) {
                self->destructor(&entry->item);
            }

            entry->item = item;
            return;
        }

        entry = list_next(self->entry_list);
    }

    list_push(self->entry_list, entry_new(string_dup(key), item));
}

void *
dict_get(dict_t *self, const char *key) {
    entry_t *entry = list_start(self->entry_list);
    while (entry) {
        if (string_equal(entry->key, key)) {
            return entry->item;
        }

        entry = list_next(self->entry_list);
    }

    return NULL;
}

void *
dict_get_or_fail(dict_t *self, const char *key) {
    void *item = dict_get(self, key);
    if (!item) {
        fprintf(stderr, "[dict_get_or_fail] undefined key: %s\n", key);
        exit(1);
    }

    return item;
}

bool
dict_has(dict_t *self, const char *key) {
    void *item = dict_get(self, key);
    if (item) {
        return true;
    } else {
        return false;
    }
}
