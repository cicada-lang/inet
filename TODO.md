`@inspect` -- as an `op_t` to show the whole net

support primitive value

- learn for other inet implementations

[maybe] `wire/inspect` -- instead of
[maybe] `wire/connect` -- instead of `@connect`

# error handling

improve error handling -- just use `assert(value && message)`?

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`

# debug

a single thread debug mode, which record all the allocated nodes.
