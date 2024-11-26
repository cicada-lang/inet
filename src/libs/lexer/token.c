#include "index.h"

token_t *
token_new(char *string, size_t start, size_t end) {
    token_t *self = allocate(sizeof(token_t));
    self->string = string;
    self->start = start;
    self->end = end;
    return self;
}

void
token_destroy(token_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        token_t *self = *self_pointer;
        free(self->string);
        free(self);
        *self_pointer = NULL;
    }
}
