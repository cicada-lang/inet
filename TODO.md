# stack

[stack] use list of arrays -- should not need require a `size`

# lang

`worker_inspect`
`worker_test` -- call `worker_inspect`

`mod_t` -- has `filename` and `text`
`mod_load`

`eval` -- dispatch by different runes

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
