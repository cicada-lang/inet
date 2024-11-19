`parser` -- `parse_rule_second_name` report in context
`parser` -- `parser_parse_define_node_stmt` report on no name after rune
`parser` -- `parser_parse_define_program_stmt` report on no name after rune

`parser` with optional `file_name` -- error report with `file_name`

merge `mod_test` to `worker_test`
rename `worker_test` to `emit_test`
move `emit` to `syntax`

`emit` -- take token (like `compile`) instead of string
`emit` -- report error in context

`mod` with optional `file_name` -- error report with `file_name`

`commands/` add a command to do snapshot testing

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
