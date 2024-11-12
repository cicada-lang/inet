#pragma once

struct stmt_t { stmt_tag_t tag; };

// * -- define_node_stmt_t
// ! -- define_rule_stmt_t
// = -- define_program_stmt_t
// . -- run_program_stmt_t

struct define_node_stmt_t { stmt_tag_t tag; };
struct define_rule_stmt_t { stmt_tag_t tag; };
struct define_program_stmt_t { stmt_tag_t tag; };
struct run_program_stmt_t { stmt_tag_t tag; };
