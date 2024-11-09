`edge_set_first_port` & `edge_set_second_port`

`mod_new`
`mod_destroy`

`worker_new`
`worker_destroy`

`program_new`
`program_destroy`

`frame_new`
`frame_destroy`

`rule_new`
`rule_destroy`

`op_run`
`worker_interact`
`worker_run`

test -- build mod by hand and run by worker

# learn

re-read scalable-c and make mimors to remember

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?

# debug

a single thread debug mode, which record all the allocated nodes.
