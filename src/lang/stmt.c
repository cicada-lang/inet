#include "index.h"

define_node_stmt_t *
define_node_stmt_new(char *name) {
    define_node_stmt_t *self = allocate(sizeof(define_node_stmt_t));
    self->tag = DEFINE_NODE_STMT;
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

void
define_node_stmt_destroy(define_node_stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        define_node_stmt_t *self = *self_pointer;
        free(self->name);
        list_destroy(&self->input_name_list);
        list_destroy(&self->output_name_list);
        free(self);
        *self_pointer = NULL;
    }
}

define_rule_stmt_t *
define_rule_stmt_new(char *first_name, char *second_name, list_t *token_list) {
    define_rule_stmt_t *self = allocate(sizeof(define_rule_stmt_t));
    self->tag = DEFINE_RULE_STMT;
    self->first_name = first_name;
    self->second_name = second_name;
    self->token_list = token_list;
    return self;
}

void
define_rule_stmt_destroy(define_rule_stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        define_rule_stmt_t *self = *self_pointer;
        free(self->first_name);
        free(self->second_name);
        list_destroy(&self->token_list);
        free(self);
        *self_pointer = NULL;
    }
}

define_program_stmt_t *
define_program_stmt_new(char *name, list_t *token_list) {
    define_program_stmt_t *self = allocate(sizeof(define_program_stmt_t));
    self->tag = DEFINE_PROGRAM_STMT;
    self->name = name;
    self->token_list = token_list;
    return self;
}
