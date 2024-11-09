`op_exe_destroy`

`op_app_new`
`op_app_destroy`

`op_con_new`
`op_con_destroy`

`op_fpt_new`
`op_fpt_destroy`

`op_destroy`

`program_new` -- setup `op_destroy`

`spec_destroy`
`mod_destroy` -- setup `spec_destroy`

`worker_interact` -- take one `active_edge` from `active_edge_list`
`worker_step`
`worker_run` -- finish `frame_stack`

inline `free_port_group_t` to `frame_t`
`frame_t` API about `free_port_group_t`

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
