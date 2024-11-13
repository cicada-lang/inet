`interpret` -- . -- `run_program_stmt_t`
`interpret` -- ! -- `define_node_stmt_t` -- handle ports
`interpret` -- ! -- `define_rule_stmt_t`

`emit_word`

# later

`@inspect` -- as an `op_t` to show the whole net

# error handling

improve error handling -- just use `assert(value && message)`?

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`

# debug

a single thread debug mode, which record all the allocated nodes.
