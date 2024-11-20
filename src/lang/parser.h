#pragma once

struct parser_t {
    const char *src;
    const char *text;
    file_t *err;
    list_t *token_list;
    list_t *stmt_list;
};

parser_t *parser_new(void);
void parser_destroy(parser_t **self_pointer);

void parser_parse(parser_t *self);
