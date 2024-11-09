`worker_new`
`worker_destroy`

`program_new`
`program_destroy`

`frame_new`
`frame_destroy`

`rule_new`
`rule_destroy`

`program_spec_new`
`program_spec_destroy`

`spec_destroy`

`mod_destroy` -- setup `rule_destroy` and `spec_destroy`

`worker_interact` -- take one `active_edge` from `active_edge_list`
`worker_step`
`worker_run` -- finish `frame_stack`

`op_execute`

test -- build mod by hand and run by worker

# learn

re-read scalable-c and make mimors to remember

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?

# debug

a single thread debug mode, which record all the allocated nodes.
