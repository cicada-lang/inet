#include "index.h"

typedef struct node_t node_t;

struct node_t {
    node_t *prev;
    node_t *next;
    void *item;
};

struct list_t {
    node_t *first;
    node_t *last;
    node_t *cursor;
    size_t length;
    list_item_destructor_t *item_destructor;
};

list_t *
list_new(void) {
    list_t *self = allocate(sizeof(list_t));
    return self;
}

void
list_destroy(list_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        list_t *self = *self_pointer;
        list_purge(self);
        free(self);
        *self_pointer = NULL;
    }
}

void
list_purge(list_t *self) {
    assert(self);

    node_t *node = self->first;
    while (node) {
        node_t *next = node->next;
        if (self->item_destructor)
            self->item_destructor(&node->item);
        free(node);
        node = next;
    }

    self->first = NULL;
    self->last = NULL;
    self->cursor = NULL;
    self->length = 0;
}

void
list_set_item_destructor(
    list_t *self,
    list_item_destructor_t *item_destructor
) {
    self->item_destructor = item_destructor;
}

list_t *
list_new_with(list_item_destructor_t *item_destructor) {
    list_t *self = list_new();
    self->item_destructor = item_destructor;
    return self;
}

size_t
list_length(const list_t *self) {
    return self->length;
}

bool
list_is_empty(const list_t *self) {
    return self->length == 0;
}

bool
list_has(const list_t *self, void *item) {
    assert(self);
    node_t *node = self->first;
    while (node) {
        if (node->item == item) return true;
        node = node->next;
    }

    return false;
}

bool
list_remove(list_t *self, void *item) {
    node_t *node = self->first;

    while (node != NULL) {
        if (node->item == item) break;
        node = node->next;
    }

    if (!node) return false;

    if (node->next)
        node->next->prev = node->prev;
    if (node->prev)
        node->prev->next = node->next;


    if (self->cursor == node)
        self->cursor = NULL;
    if (self->first == node)
        self->first = node->next;
    if (self->last == node)
        self->last = node->prev;

    free(node);
    self->length--;
    return true;
}

void *
list_current(const list_t *self) {
    assert(self);
    if (self->cursor)
        return self->cursor->item;
    else
        return NULL;
}

void *
list_first(const list_t *self) {
    assert(self);
    if (self->first)
        return self->first->item;
    else
        return NULL;
}

void *
list_last(const list_t *self) {
    assert(self);
    if (self->last)
        return self->last->item;
    else
        return NULL;
}

void *
list_start(list_t *self) {
    assert(self);
    self->cursor = self->first;
    return list_current(self);
}

void *
list_next(list_t *self) {
    assert(self);
    self->cursor = self->cursor
        ? self->cursor->next
        : self->first;
    return list_current(self);
}

void *
list_prev(list_t *self) {
    assert(self);
    self->cursor = self->cursor
        ? self->cursor->prev
        : self->last;
    return list_current(self);
}

void *
list_end(list_t *self) {
    assert(self);
    self->cursor = self->last;
    return list_current(self);
}

void
list_push(list_t *self, void *item) {
    node_t *node = allocate(sizeof(node_t));
    assert(node);
    node->item = item;

    if (self->last) {
        self->last->next = node;
        node->prev = self->last;
        node->next = NULL;
    } else {
        self->first = node;
        node->prev = NULL;
        node->next = NULL;
    }

    self->last = node;
    self->length++;
}

void *
list_pop(list_t *self) {
    if (self->cursor == self->last)
        self->cursor = NULL;

    node_t *node = self->last;
    if (!node) return NULL;

    if (self->first == node)
        self->first = NULL;

    void *item = node->item;

    if (node->prev) {
        self->last = node->prev;
        self->last->next = NULL;
    } else {
        self->last = NULL;
    }

    free(node);
    self->length--;

    return item;
}

void
list_unshift(list_t *self, void *item) {
    node_t *node = allocate(sizeof(node_t));
    assert(node);
    node->item = item;

    if (self->first) {
        self->first->prev = node;
        node->next = self->first;
        node->prev = NULL;
    } else {
        self->last = node;
        node->next = NULL;
        node->prev = NULL;
    }

    self->first = node;
    self->length++;
}

void *
list_shift(list_t *self) {
    if (self->cursor == self->first)
        self->cursor = NULL;

    node_t *node = self->first;
    if (!node) return NULL;

    if (self->last == node)
        self->last = NULL;

    void *item = node->item;

    if (node->next) {
        self->first = node->next;
        self->first->prev = NULL;
    } else {
        self->first = NULL;
    }

    free(node);
    self->length--;

    return item;
}
