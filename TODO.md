`list_item_destroy_t` instead of `list_item_free_t`

- use `string_destroy` to test with string

`list_t` can store primitive (non-pointer) data

`stack_t` -- `stack_new`
`stack_t` -- `stack_destroy`
`stack_t` -- `stack_pop`
`stack_t` -- `stack_push`
`stack_t` -- `stack_is_empty`

`stack_test`

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
