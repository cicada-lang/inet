#pragma once

typedef enum {
    DEFINE_NODE_STMT,
    DEFINE_RULE_STMT,
    DEFINE_PROGRAM_STMT,
    RUN_PROGRAM_STMT,
} stmt_tag_t;

typedef struct stmt_t stmt_t;
typedef struct define_node_stmt_t define_node_stmt_t;
typedef struct define_rule_stmt_t define_rule_stmt_t;
typedef struct define_program_stmt_t define_program_stmt_t;
typedef struct run_program_stmt_t run_program_stmt_t;
typedef struct parser_t parser_t;
