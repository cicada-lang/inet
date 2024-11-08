# stack

[stack] `stack_size`
[stack] `stack_destroy`
[stack] `stack_purge`
[stack] `stack_length`
[stack] `stack_is_empty`
[stack] `stack_pop`
[stack] `stack_push`

# lang

[lang] `op_run`
[lang] `worker_interact`
[lang] `worker_run`
[lang] test -- build mod by hand and run by worker

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?

# debug

a single thread debug mode, which record all the allocated nodes.
