#pragma once

struct stmt_t { stmt_tag_t tag; };

// * -- define_node_stmt_t
// ! -- define_rule_stmt_t
// = -- define_program_stmt_t
// . -- run_program_stmt_t

struct define_node_stmt_t {
    stmt_tag_t tag;
    char *name;
    list_t *input_name_list;
    list_t *output_name_list;
};

struct define_rule_stmt_t {
    stmt_tag_t tag;
};

struct define_program_stmt_t {
    stmt_tag_t tag;
};

struct run_program_stmt_t {
    stmt_tag_t tag;
};

define_node_stmt_t *define_node_stmt_new(char *name);
define_rule_stmt_t *define_rule_stmt_new(void);
define_program_stmt_t *define_program_stmt_new(void);
run_program_stmt_t *run_program_stmt_new(void);

void define_node_stmt_destroy(define_node_stmt_t **self_pointer);
void define_rule_stmt_destroy(define_rule_stmt_t **self_pointer);
void define_program_stmt_destroy(define_program_stmt_t **self_pointer);
void run_program_stmt_destroy(run_program_stmt_t **self_pointer);
