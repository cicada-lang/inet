#pragma once

struct parser_t {
    const char *src;
    const char *text;
    lexer_t *lexer;
    list_t *token_list;
    list_t *stmt_list;
    file_t *err;
};

parser_t *parser_new(void);
void parser_destroy(parser_t **self_pointer);

void parser_parse(parser_t *self);
