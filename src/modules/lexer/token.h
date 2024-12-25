#pragma once

struct token_t {
    char *string;
    token_kind_t kind;
    size_t start, end;
    size_t lineno; // index from 1
    size_t column; // index from 1, end of token
    union {
        int64_t int_value;
        double float_value;
    };
};

token_t *token_new(char *string, token_kind_t kind, size_t start, size_t end, size_t lineno, size_t column);
void token_destroy(token_t **self_pointer);
