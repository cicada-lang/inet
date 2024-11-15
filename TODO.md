`spec_name` -- handle `builtin_spec_t`
`spec_print` -- handle `builtin_spec_t`

`call_builtin_op_t`

`emit_call` -- handle `builtin_spec_t`

`@connect` -- as a builtin -- instead of an `op_t` -- remove `connect_op_t`
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
