`string` -- `string_count_char`

`parser` -- `parse_rule_first_name` report in context
`parser` -- `parse_rule_first_name` use `string_count_char`
`parser` -- `parse_rule_second_name` report in context

`commands/` add a command to snapshot testing

# example

`examples/combinators.inet` -- interaction combinators
`examples/lambda.inet` -- use interaction combinators

# docs

docs/articles/programming-with-interaction-nets.md -- update for new syntax
docs/articles/反应网编程.md -- update for new syntax

# linear local variables

`op_let_local_t`
`op_use_local_t`

```
1 $name  // let name = 1
...
name     // use name (after then name is free to use again)
```

# lang

`value_t` as sumtype with `WIRE_VALUE`

# parallelism

learn linux thread

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

# debug

a single thread debug mode, which record all the allocated nodes.
