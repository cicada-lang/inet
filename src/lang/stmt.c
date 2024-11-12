#include "index.h"

define_node_stmt_t *
define_node_stmt_new(char *name) {
    define_node_stmt_t *self = allocate(sizeof(define_node_stmt_t));
    self->name = name;

    self->input_name_list = list_new();
    list_set_item_destructor(
        self->input_name_list,
        (list_item_destructor_t *) string_destroy);

    self->output_name_list = list_new();
    list_set_item_destructor(
        self->output_name_list,
        (list_item_destructor_t *) string_destroy);

    return self;
}
