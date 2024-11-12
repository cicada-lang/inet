#include "index.h"

parser_t *
parser_new(list_t *token_list) {
    parser_t *self = allocate(sizeof(parser_t));
    self->token_list = token_list;

    self->stmt_list = list_new();
    list_set_item_destructor(
        self->stmt_list,
        (list_item_destructor_t *) stmt_destroy);

    return self;
}

void
parser_destroy(parser_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        parser_t *self = *self_pointer;
        list_destroy(&self->token_list);
        // keep `stmt_list` to be collected as return value.
        free(self);
        *self_pointer = NULL;
    }
}

void
parser_parse(parser_t *self) {
    (void) self;
}

list_t *
parse(list_t *token_list) {
    parser_t *parser = parser_new(token_list);
    parser_parse(parser);
    list_t *stmt_list = parser->stmt_list;
    parser_destroy(&parser);
    return stmt_list;
}
