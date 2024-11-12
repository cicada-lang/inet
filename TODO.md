`get_free_wire` -- should consume `free_wire_group`
`worker_interact` and `worker_run` take `debug` flag
`frame_print` -- show `active_pair_list`

`@inspect` -- as an `op_t` to show the how net

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

`mod_load`

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`

# debug

a single thread debug mode, which record all the allocated nodes.
