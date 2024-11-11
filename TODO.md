`spec_print`
`mod_print` -- with `spec_print`

`port_print`
`worker_print` -- print `port_stack`

`frame_print`
`worker_print` -- print `frame_stack`

`worker_test` -- call `worker_print`

`token_t`
`lexer_t`
`lexer_lex`

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

`mod_t` -- has `filename` and `text`
`mod_load`

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`

# debug

a single thread debug mode, which record all the allocated nodes.
