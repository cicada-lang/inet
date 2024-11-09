`free_port_group_destroy`

`frame_new` -- fix `first_free_port_group` and `second_free_port_group`

`frame_destroy`

`worker_new` -- setup `frame_destroy`

`rule_new`
`rule_destroy`

`program_spec_new`
`program_spec_destroy`

`op_destroy`

`program_new` -- setup `op_destroy`

`spec_destroy`

`mod_destroy` -- setup `rule_destroy` and `spec_destroy`

`worker_interact` -- take one `active_edge` from `active_edge_list`
`worker_step`
`worker_run` -- finish `frame_stack`

`op_execute`

test -- build mod by hand and run by worker

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
