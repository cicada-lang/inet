`free_port_group_t`

- A `port_t` is a free port
  if it is not linked to a node
  and it's `port_index` is -1.

`frame_t` -- has `first_free_port_group` and `second_free_port_group`

- The free ports in a frame can be referenced by `op_fpt_t`.

`stack_t` -- like `list`, be a generic data structure

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
