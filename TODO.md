docs/articles/programming-with-interaction-nets.md -- update for new syntax
docs/articles/反应网编程.md -- update for new syntax -- update for new syntax

`compile` -- report undefined node name in context
`compile` -- report undefined port name in context

`interpret` -- check node defined on `DEFINE_RULE_STMT`
`interpret` -- check name not defined on `DEFINE_NODE_STMT`
`interpret` -- check name not defined on `DEFINE_PROGRAM_STMT`

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

how to find rule?

- [maybe] by type -- `(node)-[primitive-value: type]`
- [maybe] by predicate `(node)-[primitive-value: predicate?]`
