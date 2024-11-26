#pragma once

#define MAX_TOKEN_LENGTH 1024

struct lexer_t {
    const char *text;
    size_t text_length;
    size_t cursor;
    char *buffer;
    size_t buffer_length;
    list_t *token_list;
};

lexer_t *lexer_new(void);
void lexer_destroy(lexer_t **self_pointer);

void lexer_lex(lexer_t *self);
