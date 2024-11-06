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
};

list_t *
list_create(void) {
    list_t *self = allocate(sizeof(list_t));
    return self;
}

void
list_destroy(list_t **self_pointer, list_item_free_t *item_free) {
    assert(self_pointer);
    if (*self_pointer) {
        list_t *self = *self_pointer;
        list_purge(self, item_free);
        free(self);
        *self_pointer = NULL;
    }
}

void
list_purge(list_t *self, list_item_free_t *item_free) {
    assert(self);
    node_t *node = self->first;
    while (node) {
        node_t *next = node->next;
        if (item_free)
            (item_free)(node->item);

        free(node);
        node = next;
    }

    self->first = NULL;
    self->last = NULL;
    self->cursor = NULL;
    self->length = 0;
}

size_t
list_lenght(const list_t *self) {
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

void
list_test(void) {
    printf("<list>");

    list_t *list = list_create();
    assert(list);
    assert(list_lenght(list) == 0);

    assert(list_first(list) == NULL);
    assert(list_last(list) == NULL);
    assert(list_current(list) == NULL);

    assert(list_start(list) == NULL);
    assert(list_end(list) == NULL);

    assert(list_next(list) == NULL);
    assert(list_prev(list) == NULL);

    assert(list_pop(list) == NULL);
    assert(list_shift(list) == NULL);

    //  Three items we'll use as test data
    //  List items are void *, not particularly strings
    char *cheese = string_clone("boursin");
    char *bread = string_clone("baguette");
    char *wine = string_clone("bordeaux");

    {
        list_push(list, cheese);
        assert(list_lenght(list) == 1);
        assert(list_has(list, cheese));
        assert(!list_has(list, bread));
        assert(!list_has(list, wine));

        list_push(list, bread);
        assert(list_lenght(list) == 2);
        assert(list_has(list, cheese));
        assert(list_has(list, bread));
        assert(!list_has(list, wine));

        list_push(list, wine);
        assert(list_lenght(list) == 3);
        assert(list_has(list, cheese));
        assert(list_has(list, bread));
        assert(list_has(list, wine));

        assert(list_first(list) == cheese);
        assert(list_next(list) == cheese);

        assert(list_start(list) == cheese);
        assert(list_last(list) == wine);
        assert(list_next(list) == bread);

        assert(list_start(list) == cheese);
        assert(list_next(list) == bread);
        assert(list_next(list) == wine);
        assert(list_next(list) == NULL);
        //  After we reach end of list, next wraps around
        assert(list_next(list) == cheese);
        assert(list_lenght(list) == 3);

        list_remove(list, wine);
        assert(list_lenght(list) == 2);

        assert(list_first(list) == cheese);
        list_remove(list, cheese);
        assert(list_lenght(list) == 1);
        assert(list_first(list) == bread);

        list_remove(list, bread);
        assert(list_lenght(list) == 0);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        assert(list_last(list) == bread);
        list_remove(list, bread);
        assert(list_last(list) == cheese);
        list_remove(list, cheese);
        assert(list_last(list) == NULL);
    }

    {
        list_unshift(list, cheese);
        assert(list_lenght(list) == 1);
        assert(list_first(list) == cheese);

        list_unshift(list, bread);
        assert(list_lenght(list) == 2);
        assert(list_start(list) == bread);
        assert(list_current(list) == bread);

        list_push(list, wine);
        assert(list_lenght(list) == 3);
        assert(list_first(list) == bread);

        list_pop(list);
        list_pop(list);
        list_pop(list);
    }

    {
        list_unshift(list, cheese);
        list_unshift(list, bread);
        list_unshift(list, wine);

        assert(list_shift(list) == wine);
        assert(list_shift(list) == bread);
        assert(list_shift(list) == cheese);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        list_push(list, wine);

        assert(list_start(list) == cheese);
        assert(list_next(list) == bread);
        assert(list_next(list) == wine);

        assert(list_shift(list) == cheese);
        assert(list_shift(list) == bread);
        assert(list_shift(list) == wine);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        list_push(list, wine);

        assert(list_end(list) == wine);
        assert(list_prev(list) == bread);
        assert(list_prev(list) == cheese);

        assert(list_pop(list) == wine);
        assert(list_pop(list) == bread);
        assert(list_pop(list) == cheese);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        list_push(list, wine);

        list_purge(list, free);
        assert(list_lenght(list) == 0);

        list_destroy(&list, free);

        assert(list == NULL);
    }

    printf("</list>\n");
}
