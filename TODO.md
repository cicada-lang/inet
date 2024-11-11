`worker_inspect`
`worker_test` -- call `worker_inspect`

`mod_t` -- has `filename` and `text`
`mod_load`

`stmt_t`

`evaluate` -- dispatch by different runes

- `;` -- `ignore_comment`
- `*` -- `define_node`
- `.` -- `run_program`
- `=` -- `define_program`
- `!` -- `define_rule`

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?

# debug

a single thread debug mode, which record all the allocated nodes.
