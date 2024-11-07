`frame_t` -- has current nodes
`op_fpt_t` -- fix structure

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
