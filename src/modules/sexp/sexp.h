#pragma once

// we do not handle (car . cdr)
// because it is only one way of
// interpreting a list of symbols.

struct sexp_t { sexp_kind_t kind; };

struct atom_sexp_t {
    sexp_kind_t kind;
    const token_t *token;
};

struct list_sexp_t {
    sexp_kind_t kind;
    const token_t *start_token;
    const token_t *end_token;
    list_t *sexp_list;
};

atom_sexp_t *atom_sexp_new(const token_t *token);
void atom_sexp_destroy(atom_sexp_t **self_pointer);

list_sexp_t *list_sexp_new(const token_t *start_token, const token_t *end_token, list_t *sexp_list);
void list_sexp_destroy(list_sexp_t **self_pointer);

void sexp_destroy(sexp_t **self_pointer);

list_t *sexp_parse_list(const char *string);
sexp_t *sexp_parse(const char *string);

void sexp_print(const sexp_t *self, file_t *file);
