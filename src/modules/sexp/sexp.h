#pragma once

struct sexp_t { sexp_kind_t kind; };
struct symbol_sexp_t { sexp_kind_t kind; char *string; };
struct list_sexp_t { sexp_kind_t kind; list_t *sexp_list; };
