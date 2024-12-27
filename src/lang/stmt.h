#pragma once

typedef enum {
    DEFINE_NODE_STMT,
    DEFINE_RULE_STMT,
    DEFINE_PROGRAM_STMT,
    RUN_PROGRAM_STMT,
} stmt_kind_t;

struct stmt_t { stmt_kind_t kind; };

// * -- define_node_stmt_t
// ! -- define_rule_stmt_t
// = -- define_program_stmt_t
// . -- run_program_stmt_t

struct define_node_stmt_t {
    stmt_kind_t kind;
    token_t *head_token;
    char *name;
    list_t *input_token_list;
    list_t *output_token_list;
};

struct define_rule_stmt_t {
    stmt_kind_t kind;
    token_t *head_token;
    char *first_name;
    char *second_name;
    list_t *token_list;
};

struct define_program_stmt_t {
    stmt_kind_t kind;
    token_t *head_token;
    char *name;
    list_t *token_list;
};

struct run_program_stmt_t {
    stmt_kind_t kind;
    list_t *token_list;
};

define_node_stmt_t *define_node_stmt_new(
    token_t *head_token,
    char *name);
define_rule_stmt_t *define_rule_stmt_new(
    token_t *head_token,
    char *first_name,
    char *second_name,
    list_t *token_list);
define_program_stmt_t *define_program_stmt_new(
    token_t *head_token,
    char *name,
    list_t *token_list);
run_program_stmt_t *run_program_stmt_new(
    list_t *token_list);

void define_node_stmt_destroy(define_node_stmt_t **self_pointer);
void define_rule_stmt_destroy(define_rule_stmt_t **self_pointer);
void define_program_stmt_destroy(define_program_stmt_t **self_pointer);
void run_program_stmt_destroy(run_program_stmt_t **self_pointer);

void stmt_destroy(stmt_t **self_pointer);
