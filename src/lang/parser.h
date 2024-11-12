#pragma once

struct parser_t {
    list_t *token_list;
    list_t *stmt_list;
};

parser_t *parser_new(list_t *token_list);
void parser_destroy(parser_t **self_pointer);

void parser_parse(parser_t *self);
list_t *parse(list_t *token_list);
