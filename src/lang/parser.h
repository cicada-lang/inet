#pragma once

struct parser_t {
    const char *src;
    const char *text;
    list_t *token_list;
    list_t *stmt_list;
};

parser_t *parser_new(const char *src, const char *text);
void parser_destroy(parser_t **self_pointer);

void parser_parse(parser_t *self);
