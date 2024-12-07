#pragma once

// double linked list, with a private cursor.

list_t *list_new(void);
void list_destroy(list_t **self_pointer);
void list_purge(list_t *self);

void list_set_destructor(list_t *self, destructor_t *destructor);
list_t *list_new_with(destructor_t *destructor);

size_t list_length(const list_t *self);
bool list_is_empty(const list_t *self);
bool list_has(const list_t *self, void *item);
bool list_remove(list_t *self, void *item);

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
