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
