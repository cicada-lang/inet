#pragma once

typedef enum {
    DEFINE_NODE_STMT,
    DEFINE_RULE_STMT,
    DEFINE_FUNCTION_STMT,
    BEGIN_FUNCTION_STMT,
} stmt_kind_t;

typedef struct stmt_t stmt_t;
typedef struct define_node_stmt_t define_node_stmt_t;
typedef struct define_rule_stmt_t define_rule_stmt_t;
typedef struct define_function_stmt_t define_function_stmt_t;
typedef struct begin_function_stmt_t begin_function_stmt_t;
typedef struct parser_t parser_t;
