#pragma once

struct lexer_t {
    list_t *token_list;
    const char *text;
    size_t text_length;
    size_t cursor;
    char *buffer;
    char *buffer_max_length;
};
