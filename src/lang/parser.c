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
        list_destroy(&self->stmt_list);
        free(self);
        *self_pointer = NULL;
    }
}
