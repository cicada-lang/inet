`@inspect` -- as an `op_t` to show the whole net

# module system

use `module/name` syntax

`wire` as a builtin module, maybe use `@wire`

[maybe] `wire/inspect` -- instead of
[maybe] `wire/connect` -- instead of `@connect`

# primitive value

support primitive value

- dispatching but type -- `(node)-[primitive-value: type]`
  - `[primitive-value]` in a box.
    - box wastes memory, should just let node's port be able to store any value.

- learn for other inet implementations

# error handling

improve error handling -- just use `assert(value && message)`?

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`

# debug

a single thread debug mode, which record all the allocated nodes.
