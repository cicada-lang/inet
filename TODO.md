builtins/import_builtins.c

`@worker/print`
`@worker/print-value-stack`
`@worker/print-return-stack`

`@wire/pair`

`value_t` as sum type with `WIRE_VALUE`

# linear local variables

```
1 $name  // let name = 1
...
name     // use name (after then name is free to use again)
```

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- use `@wire/pair $name ... diff ... name`

# docs

docs/articles/programming-with-interaction-nets.md -- update for new syntax
docs/articles/反应网编程.md -- update for new syntax

# example

`examples/combinators.inet` -- interaction combinators
`examples/lambda.inet` -- use interaction combinators

# parallelism

# primitive value

support primitive value

- dispatching but type -- `(node)-[primitive-value: type]`
  - `[primitive-value]` in a box.
    - box wastes memory, should just let node's port be able to store any value.

- learn for other inet implementations

# module system

use `module/name` syntax

`wire/` as a builtin module

- [maybe] use `@wire/`

[maybe] `@wire/inspect` -- instead of `@inspect`
[maybe] `@wire/connect` -- instead of `@connect`

# error handling

improve error handling -- just use `assert(value && message)`?

# debug

a single thread debug mode, which record all the allocated nodes.
