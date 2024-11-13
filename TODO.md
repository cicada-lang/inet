`parser_parse_define_node_stmt`

`parser_test`

`worker_load` -- take `src` and `text`, create `mod` and call `worker_execute_stmt`

# later

`@inspect` -- as an `op_t` to show the whole net

# error handling

improve error handling -- just use `assert(value && message)`?

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`

# debug

a single thread debug mode, which record all the allocated nodes.
