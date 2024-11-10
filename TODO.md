`worker_step` -- handle tail-call here

`execute` -- `op_call_program`
`execute` -- `op_connect`
`execute` -- `op_get_free_port`
`execute` -- `op_call_node`

`worker_test` -- build `program` by hand and `worker_run`

# stack

[stack] use list of arrays -- should not need require a `size`

# learn

re-read scalable-c and make mimors to remember

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?

# debug

a single thread debug mode, which record all the allocated nodes.
