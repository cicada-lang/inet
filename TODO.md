# inet-asm & inet-emu

as an extension of xvm

```
&function-name call
&node-name call-node
&node-name &node-name/in fetch curry-node
```

# main

图灵机作为 inet 的例子 -> 读 2008-the-annotated-turing.djvu
inet -- 实现 combinators and lambda -> 重读 1997-interaction-combinators.pdf
理解 HVM -> 读 projects/others/HigherOrderCO/HVM/paper/HVM2.pdf

# study

[study] persons/yves-lafont/papers/1995-from-proof-nets-to-interaction-nets.pdf
[study] topics/computer-science/interaction-nets/2006-proof-nets-and-the-identity-of-proofs--straßburger.pdf
[study] projects/others/HigherOrderCO/HVM/paper/HVM2.pdf
[study] [maybe] persons/jean-yves-girard/proof-nets--the-parallel-syntax-for-proof-theory--1995.pdf

# example

[example] `examples/combinators.inet` -- interaction combinators
[example] `examples/lambda.inet` -- use interaction combinators
[example] `examples/turing.inet` -- coding turing machine

# debug

[debug] 尝试使用真实的物理学来实现 force
[debug] `node_physics_simulate` -- move by `velocity` and clear `force` for every `node_model`
[debug] remove `node_physics_fake_simulate`

# module system

在 inet-asm & inet-emu 的想法之后，
就不应该用 `module/name` 这种语法来处理模块系统了。
应该支持简单的 import name，同时支持修改 name 以避免冲突。

# primitive value

[question] how to find rule?

- [maybe] by type -- `(node)-[primitive-value: type]`
  - can not use type, because type is complicated compound data.

- [maybe] by predicate `(node)-[primitive-value: predicate?]`

  - the builtin primitive functions + builtin primitive datatypes,
    (without interaction nets) forms a forth-like language.

  - a primitive function is generic in the sense that,
    if it is applied to a wire (not-yet-value in NbE),
    it will build a eliminatior node.

[question] is it possible to have a generic `dup` that can dup any net with a root wire?

`value_t` as sumtype with `WIRE_VALUE` -- every value is under a pointer

[design] write `list-map` as example

- use explicit `dup` -- keep linear variable like `(<node>)-<port>` simple
- use `{ ... }` for un-named program -- just program, no closure over linear variables

[design] node ports can store any value -- not only wire, but also primitive values

[example] polish parsing (from 1990-interaction-nets) as an example -- need primitive string type

[question] is it possible to have a generic `dup` that can dup any net with a root wire?

# parallelism

learn linux thread

keep a single thread debug mode, which record all the allocated nodes.

# inet-lisp

do a inet-lisp for scalable syntax.
