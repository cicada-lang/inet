#pragma once

// we do not handle (car . cdr)
// because it is only one way of
// interpreting a list of symbols.

struct sexp_t { sexp_kind_t kind; };
struct symbol_sexp_t { sexp_kind_t kind; const token_t *token; };
struct list_sexp_t { sexp_kind_t kind; list_t *sexp_list; };

symbol_sexp_t *symbol_sexp_new(const token_t *token);
void symbol_sexp_destroy(symbol_sexp_t **self_pointer);

list_sexp_t *list_sexp_new(void);
void list_sexp_destroy(list_sexp_t **self_pointer);

void sexp_destroy(sexp_t **self_pointer);
