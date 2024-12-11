#pragma once

// double linked list, with a private cursor.

list_t *list_new(void);
void list_destroy(list_t **self_pointer);
void list_purge(list_t *self);

void list_set_destroy_fn(list_t *self, destroy_t *destroy);
void list_set_equal_fn(list_t *self, equal_t *equal);

list_t *list_new_with(destroy_t *destroy);

size_t list_length(const list_t *self);
bool list_is_empty(const list_t *self);
bool list_has(const list_t *self, const void *item);
bool list_remove(list_t *self, void *item);

// Find an item in the list, searching from the start.
// Uses the injected `equal`, if any, else compares item values directly.
// Returns the item handle found, or NULL.
// Sets the cursor to the found item, if any.
void *list_find(list_t *self, const void *item);

void *list_current(const list_t *self);

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

// at the index of the list.

void *list_get(list_t *self, size_t index);
