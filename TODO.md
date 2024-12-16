# debug
find . | ag net_layout
[debug] `node_model_t` has `position` and `velocity`

```c
struct node_state_t {
    vec2_t position;
    vec2_t velocity;
    vec2_t force;
};
```

[debug] `net_model` should have a `force_list`

- so that we can switch from one group of forces to another by clicking a button

[debug] `net_model` has `node_model_hash` and `node_hash`

[debug] should `step` and `run` button -- 不要显示 stack（因为未来可能是 lisp）
[core] rename function with "run" to other names -- to rename `interact` to `run`
[core] rename `interact` to `run` -- to have a `run` button

[debug] 尝试使用真实的物理学来实现 force

[debug] 建立临时的 file 用来 print，从 file 收集 string -- 可能又需要学 linux 的 API。

- 这是为了显示带有角标的 node。

# study

[study] persons/yves-lafont/papers/1995-from-proof-nets-to-interaction-nets.pdf
[study] topics/computer-science/interaction-nets/2006-proof-nets-and-the-identity-of-proofs--straßburger.pdf
[study] projects/others/HigherOrderCO/HVM/paper/HVM2.pdf

[maybe] persons/jean-yves-girard/proof-nets--the-parallel-syntax-for-proof-theory--1995.pdf

# example

`examples/combinators.inet` -- interaction combinators
`examples/lambda.inet` -- use interaction combinators

# module system

use `module/name` syntax

- we already using use name such as `wire-pair`,
  thus module syntax should just map name like `module/name` to value.

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
