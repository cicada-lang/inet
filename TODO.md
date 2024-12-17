# study

[study] persons/yves-lafont/papers/1995-from-proof-nets-to-interaction-nets.pdf
[study] topics/computer-science/interaction-nets/2006-proof-nets-and-the-identity-of-proofs--straßburger.pdf
[study] projects/others/HigherOrderCO/HVM/paper/HVM2.pdf

[maybe] persons/jean-yves-girard/proof-nets--the-parallel-syntax-for-proof-theory--1995.pdf

# example

`examples/combinators.inet` -- interaction combinators
`examples/lambda.inet` -- use interaction combinators

# inet-asm & inet-emu

inet-asm & inet-emu

应该是 xvm 的一个扩展

- 尝试看看把 inet 当作 xvm 的扩展时，byte code 是如何的
- 利用 uxn 中带有子 nametable 的 nametable
  - @add
  - @add/in-arity
  - @add/!/zero
  - @add/!/add1
  - @add/-/zero
  - @add/-/add1
  - @add/-<>-/zero
  - @add/-<>-/add1
  - @add/-<!>-/zero
  - @add/-<!>-/add1

# debug

[debug] 尝试使用真实的物理学来实现 force
[debug] `node_physics_simulate` -- move by `velocity` and clear `force` for every `node_model`
[debug] remove `node_physics_fake_simulate`

# module system

use `module/name` syntax

- we already using use name such as `wire-pair`,
  thus module syntax should just map name like `module/name` to value.

在 inet-asm & inet-emu 的想法之后，
用 `module/name` 这种语法来处理模块系统，
就要在汇编语言的层次考虑了，
或者说，就要在可执行文件的层次考虑了。

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

# inet-vm & inet-asm

making postfix language inet-asm,
do a inet-lisp for scalable syntax.
