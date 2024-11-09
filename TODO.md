`port_destroy`
- `node_destroy` -- call `port_destroy`
`port_node`
`port_set_node`
`port_index`
`port_set_index`
`port_opposite_port`
`port_set_opposite_port`

`edge_new`
`edge_destroy`
`edge_first_port`
`edge_second_port`
`edge_set_first_port`
`edge_set_second_port`

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
