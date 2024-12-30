#include "index.h"

define_node_stmt_t *
define_node_stmt_new(token_t *head_token, char *name) {
    define_node_stmt_t *self = new(define_node_stmt_t);
    self->kind = DEFINE_NODE_STMT;

    self->head_token = head_token;
    self->name = name;

    self->input_token_list = list_new_with((destroy_fn_t *) token_destroy);
    self->output_token_list = list_new_with((destroy_fn_t *) token_destroy);

    return self;
}

void
define_node_stmt_destroy(define_node_stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        define_node_stmt_t *self = *self_pointer;
        token_destroy(&self->head_token);
        free(self->name);
        list_destroy(&self->input_token_list);
        list_destroy(&self->output_token_list);
        free(self);
        *self_pointer = NULL;
    }
}

define_rule_stmt_t *
define_rule_stmt_new(
    token_t *head_token,
    char *first_name,
    char *second_name,
    list_t *token_list
) {
    define_rule_stmt_t *self = new(define_rule_stmt_t);
    self->kind = DEFINE_RULE_STMT;
    self->head_token = head_token;
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
        token_destroy(&self->head_token);
        free(self->first_name);
        free(self->second_name);
        list_destroy(&self->token_list);
        free(self);
        *self_pointer = NULL;
    }
}

define_function_stmt_t *
define_function_stmt_new(token_t *head_token, char *name, list_t *token_list) {
    define_function_stmt_t *self = new(define_function_stmt_t);
    self->kind = DEFINE_FUNCTION_STMT;
    self->head_token = head_token;
    self->name = name;
    self->token_list = token_list;
    return self;
}

void
define_function_stmt_destroy(define_function_stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        define_function_stmt_t *self = *self_pointer;
        token_destroy(&self->head_token);
        free(self->name);
        list_destroy(&self->token_list);
        free(self);
        *self_pointer = NULL;
    }
}

begin_function_stmt_t *
begin_function_stmt_new(list_t *token_list) {
    begin_function_stmt_t *self = new(begin_function_stmt_t);
    self->kind = BEGIN_FUNCTION_STMT;
    self->token_list = token_list;
    return self;
}

void
begin_function_stmt_destroy(begin_function_stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        begin_function_stmt_t *self = *self_pointer;
        list_destroy(&self->token_list);
        free(self);
        *self_pointer = NULL;
    }
}

void
stmt_destroy(stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        stmt_t *self = *self_pointer;
        switch (self->kind) {
        case DEFINE_NODE_STMT: {
            define_node_stmt_destroy((define_node_stmt_t **) self_pointer);
            return;
        }

        case DEFINE_RULE_STMT: {
            define_rule_stmt_destroy((define_rule_stmt_t **) self_pointer);
            return;
        }

        case DEFINE_FUNCTION_STMT: {
            define_function_stmt_destroy((define_function_stmt_t **) self_pointer);
            return;
        }

        case BEGIN_FUNCTION_STMT: {
            begin_function_stmt_destroy((begin_function_stmt_t **) self_pointer);
            return;
        }
        }
    }
}
