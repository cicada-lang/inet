#include "index.h"

#define STACK_BLOCK_SIZE 1024

struct stack_t {
    size_t block_size;
    list_t *array_list;
    destroy_fn_t *destroy_fn;
};

stack_t *
stack_new(void) {
    stack_t *self = new(stack_t);
    self->block_size = STACK_BLOCK_SIZE;
    assert(self->block_size >= 1);
    self->array_list = list_new();
    return self;
}

void
stack_purge(stack_t *self) {
    assert(self);
    while(!stack_is_empty(self)) {
        void* value = stack_pop(self);
        if (self->destroy_fn)
            self->destroy_fn(&value);
    }
}

void
stack_destroy(stack_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        stack_t *self = *self_pointer;
        stack_purge(self);
        list_destroy(&self->array_list);
        free(self);
        *self_pointer = NULL;
    }
}

void
stack_set_destroy_fn(stack_t *self, destroy_fn_t *destroy_fn) {
    self->destroy_fn = destroy_fn;
}

stack_t *
stack_new_with(destroy_fn_t *destroy_fn) {
    stack_t *self = stack_new();
    self->destroy_fn = destroy_fn;
    return self;
}

size_t
stack_length(const stack_t *self) {
    size_t length = 0;
    array_t *array = list_first(self->array_list);
    while (array) {
        length += array_length(array);
        array = list_next(self->array_list);
    }

    return length;
}

bool
stack_is_empty(const stack_t *self) {
    return list_is_empty(self->array_list);
}

void *
stack_top(stack_t *self) {
    array_t *array = list_last(self->array_list);
    assert(array);
    return array_top(array);
}

void *
stack_pop(stack_t *self) {
    array_t *array = list_last(self->array_list);
    assert(array);
    void* value = array_pop(array);
    if (array_is_empty(array)) {
        list_pop(self->array_list);
        array_destroy(&array);
    }

    return value;
}

void
stack_push(stack_t *self, void *value) {
    array_t *array = list_last(self->array_list);
    if (!array || array_is_full(array)) {
        array = array_new(self->block_size);
        list_push(self->array_list, array);
    }

    array_push(array, value);
}

void *
stack_get(stack_t *self, size_t index) {
    array_t *array = list_get(
        self->array_list,
        index / self->block_size);

    if (!array) return NULL;

    return array_get(array, index % self->block_size);
}

void *
stack_pick(stack_t *self, size_t index) {
    return stack_get(self, stack_length(self) - index - 1);
}
