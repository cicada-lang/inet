#pragma once

struct sexp_t { sexp_kind_t kind; };
struct symbol_sexp_t { sexp_kind_t kind; const token_t *token; };
struct list_sexp_t { sexp_kind_t kind; list_t *sexp_list; };

symbol_sexp_t *symbol_sexp_new(const token_t *token);
list_sexp_t *list_sexp_new(void);

void symbol_sexp_destroy(symbol_sexp_t **self_pointer);
