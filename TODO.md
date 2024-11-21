# example

`examples/combinators.inet` -- interaction combinators
`examples/lambda.inet` -- use interaction combinators

# module system

use `module/name` syntax

- we already using use name such as `@wire/pair`,
  thus module syntax should just map name like `module/name` to value.

# parallelism

learn linux thread

keep a single thread debug mode, which record all the allocated nodes.

# primitive value

[prerequisite] linear v.s. normal value

`value_t` as sumtype with `WIRE_VALUE` -- every value is under a pointer

- use explicit `@dup` -- keep linear variable like `(<node>)-<port>` simple
  - is it possible to have a generic `@dup` that can dup any net with a root wire?
- use `{ ... }` for un-named program -- just program, no closure over linear variables

how to find rule?

- [maybe] by type -- `(node)-[primitive-value: type]`
- [maybe] by predicate `(node)-[primitive-value: predicate?]`
