#include "index.h"

typedef void *item_t;

struct stack_t {
    size_t size;
    size_t cursor;
    item_t *items;
    stack_item_destructor_t *item_destructor;
};

stack_t *
stack_new(size_t size) {
    stack_t *self = allocate(sizeof(stack_t));
    self->size = size;
    self->cursor = 0;
    self->items = allocate_pointers(size);
    return self;
}

void
stack_purge(stack_t *self) {
    assert(self);
    while(!stack_is_empty(self)) {
        item_t item = stack_pop(self);
        if (self->item_destructor)
            self->item_destructor(&item);
    }
}

void
stack_destroy(stack_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        stack_t *self = *self_pointer;
        stack_purge(self);
        free(self);
        *self_pointer = NULL;
    }
}


void
stack_set_item_destructor(
    stack_t *self,
    stack_item_destructor_t *item_destructor
) {
    self->item_destructor = item_destructor;
}

stack_t *
stack_new_with(size_t size, stack_item_destructor_t *item_destructor) {
    stack_t *self = stack_new(size);
    self->item_destructor = item_destructor;
    return self;
}

size_t
stack_size(const stack_t *self) {
    return self->size;
}

size_t
stack_length(const stack_t *self) {
    return self->cursor;
}

bool
stack_is_empty(const stack_t *self) {
    return self->cursor == 0;
}

void *
stack_top(stack_t *self) {
    assert(self->cursor > 0);
    item_t item = self->items[self->cursor - 1];
    return item;
}

void *
stack_pop(stack_t *self) {
    assert(self->cursor > 0);
    self->cursor--;
    item_t item = self->items[self->cursor];
    return item;
}

void
stack_push(stack_t *self, void *item) {
    self->items[self->cursor] = item;
    self->cursor++;
}

void *
stack_get(stack_t *self, size_t index) {
    assert(index < self->cursor);
    return self->items[index];
}

void *
stack_pick(stack_t *self, size_t index) {
    assert(index < self->cursor);
    return self->items[self->cursor - 1 - index];
}
