# linear local variables

`op_let_local_t`
`op_use_local_t`

```
1 $name  // let name = 1
...
name     // use name (after then name is free to use again)
```

# design

diff-list.inet -- re-design syntax to simplify

- remove the idea of `(diff) @spread`
- use `@wire/pair $name ... diff ... name`

# example

`examples/combinators.inet` -- interaction combinators
`examples/lambda.inet` -- use interaction combinators

# lang

`value_t` as sumtype with `WIRE_VALUE`

# docs

docs/articles/programming-with-interaction-nets.md -- update for new syntax
docs/articles/反应网编程.md -- update for new syntax

# parallelism

learn linux thread

# testing

how to add snapshot testing?

# primitive value

support primitive value

- dispatching but type -- `(node)-[primitive-value: type]`
  - `[primitive-value]` in a box.
    - box wastes memory, should just let node's port be able to store any value.

- learn for other inet implementations

# module system

use `module/name` syntax

- we already using use `@wire/`,
  maybe module is just name prefix.

# error handling

improve error handling -- just use `assert(value && message)`?

# debug

a single thread debug mode, which record all the allocated nodes.
