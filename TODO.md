`parser_parse_define_node_stmt`
`parser_parse_define_rule_stmt`
`parser_parse_define_program_stmt`
`parser_parse_run_program_stmt`

`compile_stmt` -- setup
`mod_load` -- call `compile_stmt`
`compile_stmt(stmt, mod)`
`@inspect` -- as an `op_t` to show the whole net

# error handling

improve error handling -- just use `assert(value && message)`?

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`

# debug

a single thread debug mode, which record all the allocated nodes.
