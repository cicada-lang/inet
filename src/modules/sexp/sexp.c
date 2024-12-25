#include "index.h"

symbol_sexp_t *
symbol_sexp_new(const token_t *token) {
    symbol_sexp_t *self = new(symbol_sexp_t);
    self->kind = SYMBOL_SEXP;
    self->token = token;
    return self;
}
