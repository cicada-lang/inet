#include "index.h"

symbol_sexp_t *
symbol_sexp_new(const token_t *token) {
    symbol_sexp_t *self = new(symbol_sexp_t);
    self->kind = SYMBOL_SEXP;
    self->token = token;
    return self;
}

void
symbol_sexp_destroy(symbol_sexp_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        symbol_sexp_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

list_sexp_t *
list_sexp_new(void) {
    list_sexp_t *self = new(list_sexp_t);
    self->kind = LIST_SEXP;
    self->sexp_list = list_new();
    return self;
}

void
list_sexp_destroy(list_sexp_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        list_sexp_t *self = *self_pointer;
        list_destroy(&self->sexp_list);
        free(self);
        *self_pointer = NULL;
    }
}
