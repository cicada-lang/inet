#pragma once

typedef void (list_item_destructor_t)(void **item);

// double linked list, with a private cursor.

list_t *list_new(void);
void list_destroy(list_t **self_pointer);
void list_purge(list_t *self);

void list_set_item_destructor(list_t *self, list_item_destructor_t *item_destructor);
size_t list_length(const list_t *self);
bool list_is_empty(const list_t *self);
bool list_has(const list_t *self, void *item);
bool list_remove(list_t *self, void *item);

void *list_current(const list_t *self);
void *list_first(const list_t *self);
void *list_last(const list_t *self);

// move the cursor.

void *list_start(list_t *self);
void *list_next(list_t *self);
void *list_prev(list_t *self);
void *list_end(list_t *self);

// at the end of the list.

void list_push(list_t *self, void *item);
void *list_pop(list_t *self);

// at the start of the list.

void list_unshift(list_t *self, void *item);
void *list_shift(list_t *self);
