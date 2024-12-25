#include "index.h"

token_t *
token_new(char *string, token_kind_t kind, size_t start, size_t end, size_t lineno, size_t column) {
    token_t *self = new(token_t);
    self->string = string;
    self->kind = kind;
    self->start = start;
    self->end = end;
    self->lineno = lineno;
    self->column = column;
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
