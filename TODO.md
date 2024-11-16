remove `connect_op_t`

- `@connect` -- as a builtin

`@inspect` -- as an builtin -- keep the value on stack and call `wire_inspect`

`string_to_subscript`
`wire_inspect`

```xml
<net>
<root>(add1₂₅)-value!-<>-</root>
(add1₂₅)-prev-<>-value-(add1₂₃)
(add1₂₃)-prev-<>-value-(zero₂₁)
</net>
```

# docs

docs/articles/programming-with-interaction-nets.md -- update for new syntax
docs/articles/反应网编程.md -- update for new syntax

# example

`examples/lambda.inet` -- use interaction combinators

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

# parallelism

# debug

a single thread debug mode, which record all the allocated nodes.
