extract `port_spec.c`

`port_spec_new`
`port_spec_destroy`

`node_spec_new`
`node_spec_destroy`

`node_spec_name`
`node_spec_input_arity`
`node_spec_output_arity`

`node_gen_id`
`node_new`

`port_new`
`port_set_opposite`

`op_run`
`worker_interact`
`worker_run`

test -- build mod by hand and run by worker

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?

# debug

a single thread debug mode, which record all the allocated nodes.
