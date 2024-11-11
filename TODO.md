`port_is_free_port`
`port_is_node_port`
`port_is_loss_port`

`port_print`

- free-port: `(node)-port:port~`
- node-port: `(node)-port:port-(node)`
- lossing-port: `~<loss-port>~` -- free-port without `opposite_port`

`free_port_group_print` -- fix format

- `(node) ~port:port-(node)`

`worker_test` -- define some rules

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
