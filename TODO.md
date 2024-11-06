worker -- has `active_edge_list`

rule -- has compiled byte code

mod -- has rule_list

- how to design "double names as key" kv store？
  use list first, optimize only when needed.

worker_interact

worker_run

test -- build mod by hand and run by worker

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?

# debug

a single thread debug mode, which record all the allocated nodes.
