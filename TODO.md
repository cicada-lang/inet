operation -- dynamic tagged union

| word        | operation             | comment                                                |
|-------------|-----------------------|--------------------------------------------------------|
| name        | `apply_program`       | maybe need a return stack (worker need a return stack) |
| name        | `apply_node`          | input claim free ports, output create new free ports   |
| (node)-port | `get_free_port`       | push a free port to the stack                          |
| port-(node) | `reconnect_free_port` | (node)-port @connect                                   |
| @connect    | `connect`             |                                                        |

the above feels like a little forth already!

program -- has `operation_list` -- let's do NOT optimize!

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
