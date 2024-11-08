#include "index.h"

typedef void *item_t;

struct stack_t {
    size_t size;
    size_t cursor;
    item_t *items;
};

stack_t *
stack_new(size_t size) {
    stack_t *self = allocate(sizeof(stack_t));
    self->size = size;
    self->cursor = 0;
    self->items = allocate_array(size, sizeof(item_t));
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
