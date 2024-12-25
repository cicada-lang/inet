#pragma once

struct token_t {
    char *string;
    token_kind_t kind;
    size_t start, end;
    size_t lineno, column;
};

token_t *token_new(char *string, token_kind_t kind, size_t start, size_t end, size_t lineno, size_t column);
void token_destroy(token_t **self_pointer);
