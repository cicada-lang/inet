#include "index.h"

struct array_t {
    size_t size;
    size_t cursor;
    void **items;
    destroy_fn_t *destroy_fn;
};

array_t *
array_new(size_t size) {
    array_t *self = new(array_t);
    self->size = size;
    self->cursor = 0;
    self->items = allocate_pointers(size);
    return self;
}

void
array_purge(array_t *self) {
    assert(self);
    while(!array_is_empty(self)) {
        void *item = array_pop(self);
        if (self->destroy_fn)
            self->destroy_fn(&item);
    }
}

void
array_destroy(array_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        array_t *self = *self_pointer;
        array_purge(self);
        free(self);
        *self_pointer = NULL;
    }
}


void
array_set_destroy_fn(array_t *self, destroy_fn_t *destroy_fn) {
    self->destroy_fn = destroy_fn;
}

array_t *
array_new_with(size_t size, destroy_fn_t *destroy_fn) {
    array_t *self = array_new(size);
    self->destroy_fn = destroy_fn;
    return self;
}

size_t
array_size(const array_t *self) {
    return self->size;
}

size_t
array_length(const array_t *self) {
    return self->cursor;
}

bool
array_is_empty(const array_t *self) {
    return self->cursor == 0;
}

bool
array_is_full(const array_t *self) {
    return self->cursor == self->size;
}

void *
array_top(array_t *self) {
    assert(self->cursor > 0);
    void *item = self->items[self->cursor - 1];
    return item;
}

void *
array_pop(array_t *self) {
    assert(self->cursor > 0);
    self->cursor--;
    void *item = self->items[self->cursor];
    return item;
}

void
array_push(array_t *self, void *item) {
    self->items[self->cursor] = item;
    self->cursor++;
}

void *
array_get(array_t *self, size_t index) {
    assert(index < self->cursor);
    return self->items[index];
}

void *
array_pick(array_t *self, size_t index) {
    assert(index < self->cursor);
    return self->items[self->cursor - 1 - index];
}
