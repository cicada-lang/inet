# canvas

[canvas] extract `on_four_sides` from `canvas_fiil_rect_round`
[canvas] 从下列函数中抽出来谓词 `canvas_draw_rect`，`canvas_fiil_rect_round`，`canvas_draw_rect_round`

- 谓词是用来判断点的位置的，这些函数只是在这些位置 draw pixel，
  所以这些谓词才是重要的。

# hash

[hash] setup `hash.c`
[hash] a hash table with constant time lookup and dense iteration.

# debug

[debug] `net_layout` should have a `force_list`

- so that we can switch from one group of forces to another by clicking a button
- 为了获得更好的 abstraction，需要学习物理学知识 -- read sussman books
  可能应该抽出来：
  - `net_t` -- 专门用来遍历 net 中的元素
  - `debug_t` 应该有一个 node id 到 `particle_t` (或者类似的物理建模对象) 的 hash map

  也许不应该依赖物理知识，因为我需要的只是合理的命名而已。
  可以先把正确的代码结构写出来，再改名字。

[debug] try to add `velocity` -- 另外一种 force group

[debug] 建立临时的 file 用来 print，从 file 收集 string -- 可能又需要学 linux 的 API。

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

- we already using use name such as `@wire/pair`,
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

[question] is it possible to have a generic `@dup` that can dup any net with a root wire?

`value_t` as sumtype with `WIRE_VALUE` -- every value is under a pointer

[design] write `list-map` as example

- use explicit `@dup` -- keep linear variable like `(<node>)-<port>` simple
- use `{ ... }` for un-named program -- just program, no closure over linear variables

[design] node ports can store any value -- not only wire, but also primitive values

[example] polish parsing (from 1990-interaction-nets) as an example -- need primitive string type

[question] is it possible to have a generic `@dup` that can dup any net with a root wire?

# parallelism

learn linux thread

keep a single thread debug mode, which record all the allocated nodes.
