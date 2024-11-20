#include "index.h"

define_node_stmt_t *
define_node_stmt_new(token_t *head_token, char *name) {
    define_node_stmt_t *self = allocate(sizeof(define_node_stmt_t));
    self->tag = DEFINE_NODE_STMT;

    self->head_token = head_token;
    self->name = name;

    self->input_token_list = list_new();
    list_set_item_destructor(
        self->input_token_list,
        (list_item_destructor_t *) token_destroy);

    self->output_token_list = list_new();
    list_set_item_destructor(
        self->output_token_list,
        (list_item_destructor_t *) token_destroy);

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
    define_rule_stmt_t *self = allocate(sizeof(define_rule_stmt_t));
    self->tag = DEFINE_RULE_STMT;
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

define_program_stmt_t *
define_program_stmt_new(token_t *head_token, char *name, list_t *token_list) {
    define_program_stmt_t *self = allocate(sizeof(define_program_stmt_t));
    self->tag = DEFINE_PROGRAM_STMT;
    self->head_token = head_token;
    self->name = name;
    self->token_list = token_list;
    return self;
}

void
define_program_stmt_destroy(define_program_stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        define_program_stmt_t *self = *self_pointer;
        token_destroy(&self->head_token);
        free(self->name);
        list_destroy(&self->token_list);
        free(self);
        *self_pointer = NULL;
    }
}

run_program_stmt_t *
run_program_stmt_new(list_t *token_list) {
    run_program_stmt_t *self = allocate(sizeof(run_program_stmt_t));
    self->tag = RUN_PROGRAM_STMT;
    self->token_list = token_list;
    return self;
}

void
run_program_stmt_destroy(run_program_stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        run_program_stmt_t *self = *self_pointer;
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
        switch (self->tag) {
        case DEFINE_NODE_STMT: {
            define_node_stmt_destroy((define_node_stmt_t **) self_pointer);
            return;
        }

        case DEFINE_RULE_STMT: {
            define_rule_stmt_destroy((define_rule_stmt_t **) self_pointer);
            return;
        }

        case DEFINE_PROGRAM_STMT: {
            define_program_stmt_destroy((define_program_stmt_t **) self_pointer);
            return;
        }

        case RUN_PROGRAM_STMT: {
            run_program_stmt_destroy((run_program_stmt_t **) self_pointer);
            return;
        }
        }
    }
}
