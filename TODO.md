# docs

[docs] docs/articles/programming-with-interaction-nets.md -- update to new syntax

# later

[primitive] net -- define_node -- check_name_not_defined
[example] recover tests/ -- undefined-name.error
[example] recover tests/ -- wrong-node-name.error

# value

[value] object_spec_t
[value] xobject -- has address to object_spec_t as kind

# extending x-forth

[net] wire_t as xobject
[net] fix value_print for wire_t

# later

[example] `examples/lambda.fth` -- use interaction combinators
[example] `examples/turing.fth` -- coding turing machine

# primitive value

[design] write `list-map` as example

- use explicit `dup` -- keep linear variable like `(<node>)-<port>` simple
- use `{ ... }` for un-named program -- just program, no closure over linear variables

[design] node ports can store any value -- not only wire, but also primitive values
[example] polish parsing (from 1990-interaction-nets) as an example -- need primitive string type
[question] is it possible to have a generic `dup` that can dup any net with a root wire?

# main

图灵机作为 inet 的例子 -> 读 2008-the-annotated-turing.djvu
inet -- 实现 combinators and lambda -> 重读 1997-interaction-combinators.pdf
理解 HVM -> 读 projects/others/HigherOrderCO/HVM/paper/HVM2.pdf

# study

[study] persons/yves-lafont/papers/1995-from-proof-nets-to-interaction-nets.pdf
[study] topics/computer-science/interaction-nets/2006-proof-nets-and-the-identity-of-proofs--straßburger.pdf
[study] projects/others/HigherOrderCO/HVM/paper/HVM2.pdf
[study] [maybe] persons/jean-yves-girard/proof-nets--the-parallel-syntax-for-proof-theory--1995.pdf

# debug

[debug] 尝试使用真实的物理学来实现 force
[debug] `node_physics_simulate` -- move by `velocity` and clear `force` for every `node_model`
[debug] remove `node_physics_fake_simulate`

# module system

也许不应该用 `module/name` 这种语法来处理模块系统。
应该支持简单的 import name，同时支持修改 name 以避免冲突。

# parallelism

learn linux thread

keep a single thread debug mode, which record all the allocated nodes.
