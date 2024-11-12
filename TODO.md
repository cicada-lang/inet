`lexer_lex`
`lexer_step`
`lexer_text`

`parser_t`
`parser_parse` -- build `stmt_list` from `token_list`

- dispatch by different runes

`stmt_t`

- `;` -- `ignore_comment_stmt`
- `*` -- `define_node_stmt`
- `.` -- `run_program_stmt`
- `=` -- `define_program_stmt`
- `!` -- `define_rule_stmt`

`compile_stmt(stmt, mod)`

`@inspect` -- as an `op_t` to show the whole net

`mod_load`

# error handling

improve error handling -- just use `assert(value && message)`?

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`

# debug

a single thread debug mode, which record all the allocated nodes.
