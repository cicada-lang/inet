#include "index.h"

struct entry_t {
    char *key;
    void *value;
};

typedef struct entry_t entry_t;

entry_t *entry_new(char *key, void *value);
void entry_destroy(entry_t **self_pointer);

entry_t *
entry_new(char *key, void *value) {
    entry_t *self = new(entry_t);
    self->key = key;
    self->value = value;
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
    destroy_fn_t *destroy_fn;
};

dict_t *
dict_new(void) {
    dict_t *self = new(dict_t);
    self->entry_list = list_new_with((destroy_fn_t *) entry_destroy);
    return self;
}

void
dict_set_destroy_fn(dict_t *self, destroy_fn_t *destroy) {
    self->destroy_fn = destroy;
}

dict_t *
dict_new_with(destroy_fn_t *destroy) {
    dict_t *self = dict_new();
    self->destroy_fn = destroy;
    return self;
}

void
dict_purge(dict_t *self) {
    if (self->destroy_fn) {
        entry_t *entry = list_pop(self->entry_list);
        while (entry) {
            self->destroy_fn(&entry->value);
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
dict_set(dict_t *self, const char *key, void *value) {
    entry_t *entry = list_first(self->entry_list);
    while (entry) {
        if (string_equal(entry->key, key)) {
            if (self->destroy_fn) {
                self->destroy_fn(&entry->value);
            }

            entry->value = value;
            return;
        }

        entry = list_next(self->entry_list);
    }

    list_push(self->entry_list, entry_new(string_dup(key), value));
}

void *
dict_get(dict_t *self, const char *key) {
    entry_t *entry = list_first(self->entry_list);
    while (entry) {
        if (string_equal(entry->key, key)) {
            return entry->value;
        }

        entry = list_next(self->entry_list);
    }

    return NULL;
}

void *
dict_get_or_fail(dict_t *self, const char *key) {
    void *value = dict_get(self, key);
    if (!value) {
        fprintf(stderr, "[dict_get_or_fail] undefined key: %s\n", key);
        exit(1);
    }

    return value;
}

bool
dict_has(dict_t *self, const char *key) {
    void *value = dict_get(self, key);
    if (value) {
        return true;
    } else {
        return false;
    }
}
