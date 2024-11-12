#include "index.h"

token_t *
token_new(char *string, size_t start, size_t end) {
    token_t *self = allocate(sizeof(token_t));
    self->string = string;
    self->start = start;
    self->end = end;
    return self;
}
