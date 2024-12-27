#include "index.h"

atom_sexp_t *
atom_sexp_new(const token_t *token) {
    atom_sexp_t *self = new(atom_sexp_t);
    self->kind = ATOM_SEXP;
    self->token = token;
    return self;
}

void
atom_sexp_destroy(atom_sexp_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        atom_sexp_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

list_sexp_t *
list_sexp_new(const token_t *start_token, const token_t *end_token, list_t *sexp_list) {
    list_sexp_t *self = new(list_sexp_t);
    self->kind = LIST_SEXP;
    self->start_token = start_token;
    self->end_token = end_token;
    self->sexp_list = sexp_list;
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

void
sexp_destroy(sexp_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        sexp_t *self = *self_pointer;
        switch (self->kind) {
        case ATOM_SEXP: {
            atom_sexp_destroy((atom_sexp_t **) self_pointer);
            return;
        }

        case LIST_SEXP: {
            list_sexp_destroy((list_sexp_t **) self_pointer);
            return;
        }
        }
    }
}

static sexp_t *parse_sexp(list_t *token_list);
static list_t *parse_list(list_t *token_list);

sexp_t *
parse_sexp(list_t *token_list) {
    token_t *token = list_shift(token_list);
    if (string_equal(token->string, "(")) {
        list_t *sexp_list = parse_list(token_list);
        token_t *end_token = list_shift(token_list);
        return (sexp_t *) list_sexp_new(token, end_token, sexp_list);
    } else {
        return (sexp_t *) atom_sexp_new(token);
    }
}

list_t *
parse_list(list_t *token_list) {
    list_t *sexp_list = list_new_with((destroy_fn_t *) sexp_destroy);
    while (!list_is_empty(token_list)) {
        token_t *token = list_first(token_list);
        if (string_equal(token->string, ")"))
            return sexp_list;

        list_push(sexp_list, parse_sexp(token_list));
    }

    return sexp_list;
}

list_t *
sexp_parse_list(const char *string) {
    lexer_t *lexer = lexer_new();
    lexer->line_comment = ";";
    lexer->enable_int = true;
    lexer->enable_float = true;
    lexer->enable_string = true;
    lexer_add_delimiter(lexer, "(");
    lexer_add_delimiter(lexer, ")");

    lexer->string = string;
    lexer_run(lexer);

    list_t *result = parse_list(lexer->token_list);
    assert(list_is_empty(lexer->token_list));
    list_destroy(&lexer->token_list);
    lexer_destroy(&lexer);
    return result;
}

sexp_t *
sexp_parse(const char *string) {
    list_t *sexp_list = sexp_parse_list(string);
    sexp_t *sexp = list_shift(sexp_list);
    list_destroy(&sexp_list);
    return sexp;
}


static void
atom_sexp_print(const atom_sexp_t *atom_sexp, file_t *file) {
    switch (atom_sexp->token->kind) {
    case GENERIC_TOKEN:
    case DELIMITER_TOKEN:
    case INT_TOKEN:
    case FLOAT_TOKEN: {
        fprintf(file, "%s", atom_sexp->token->string);
        return;
    }

    case STRING_TOKEN: {
        // TODO handle \n and other \chars
        fprintf(file, "\"%s\"", atom_sexp->token->string);
        return;
    }
    }
}

static void
list_sexp_print(const list_sexp_t *list_sexp, file_t *file) {
    fprintf(file, "(");
    sexp_t *sexp = list_first(list_sexp->sexp_list);
    size_t count = 0;
    while (sexp) {
        sexp_print(sexp, file);
        if (count != list_length(list_sexp->sexp_list) - 1)
            fprintf(file, " ");
        sexp = list_next(list_sexp->sexp_list);
        count++;
    }
    fprintf(file, ")");
}

void
sexp_print(const sexp_t *self, file_t *file) {
    switch (self->kind) {
    case ATOM_SEXP: {
        atom_sexp_print((atom_sexp_t *) self, file);
        return;
    }

    case LIST_SEXP: {
        list_sexp_print((list_sexp_t *) self, file);
        return;
    }
    }
}
