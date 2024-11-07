`stack_t` -- like `list`, be a generic data structure
`frame_t` -- has current nodes
`op_fpt_t` -- fix structure
`worker_t` -- has `frame_stack`
`rule_t` -- has `program_t`
`mod_t` -- has `rule_list`

- how to design "double names as key" kv store？
  use list first, optimize only when needed.

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
