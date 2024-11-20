builtin print functions add newline

should not inject `exit_code` -- should change makefile instead

`file` -- `file_size`
`file` -- `file_remove`
`run_command` -- delete empty snapshot file

`run_command` -- snapshot for every `.test.inet` -- create `.test.inet.out` & `.test.inet.err`

change example file names

`node_new` take `id` as argument
`worker` has `node_id_count` -- test snapshot testing itself

- `inet run` -- clear node id counter for each file

merge `mod_test` to `worker_test`
rename `worker_test` to `emit_test`
move `emit` to `syntax`

`emit` -- take token (like `compile`) instead of string
`emit` -- report error in context

# docs

docs/articles/programming-with-interaction-nets.md -- update for new syntax
docs/articles/反应网编程.md -- update for new syntax

# example

`examples/combinators.inet` -- interaction combinators
`examples/lambda.inet` -- use interaction combinators

# module system

use `module/name` syntax

- we already using use `@wire/`,
  maybe module is just name prefix.

# parallelism

learn linux thread
keep a single thread debug mode, which record all the allocated nodes.

# primitive value

`value_t` as sumtype with `WIRE_VALUE`

support primitive value

- dispatching but type -- `(node)-[primitive-value: type]`
  - `[primitive-value]` in a box.
    - box wastes memory, should just let node's port be able to store any value.

- learn for other inet implementations

# linear local variables

`op_let_local_t`
`op_use_local_t`

```
1 $name  // let name = 1
...
name     // use name (after then name is free to use again)
```
