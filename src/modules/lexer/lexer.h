#pragma once

#define MAX_TOKEN_LENGTH 1024

struct lexer_t {
    const char *string;
    size_t length;

    size_t cursor;
    size_t lineno; // index from 1
    size_t column; // index from 1

    char *buffer;
    size_t buffer_length;
    list_t *token_list;
    const char *line_comment;
    list_t *delimiter_list;

    bool enable_int;
    bool enable_float;
    bool enable_string;
};

lexer_t *lexer_new(void);
void lexer_destroy(lexer_t **self_pointer);

void lexer_add_delimiter(lexer_t *self, const char *delimiter);

void lexer_run(lexer_t *self);
