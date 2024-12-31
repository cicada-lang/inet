---
title: Programming with Interaction Nets
author: Xie Yuheng
year: 2023
---

# 1

At the end of 2021,
I occasionally read a 1990 paper "Interaction Nets",
by Yves Lafont.
The paper introduced a very interesting new computation model,
using graph consists of nodes and edges as data,
and viewing interaction between connected nodes as computation.

In this paper, I will follow Lafont's examples
to introduce the principal of interaction nets.
And I will also introduce a language I designed
to program this computation model.

# 2

How to use graph to encode data?

Suppose we want to encode the simplest data -- natural number.
We can mimic the ancient knot counting, using node to do the counting.

```
0  (nzero)-
1  (nzero)-(nadd1)-
2  (nzero)-(nadd1)-(nadd1)-
3  (nzero)-(nadd1)-(nadd1)-(nadd1)-
```

The node representing 0 `(nzero)-` has one port,
the node representing +1 `-(nadd1)-` has two ports,
we can encode natural number
by connecting these nodes through the ports.

# 3

How to use graph to represent functions that operate on natural numbers?

Take naddition as an example, we need to introduce a new node to represent naddition,
and to define interaction rules between this node and other nodes.

We use a node with three ports to represent naddition.

```
       |
     (nadd)
     /   \
```

The two ports below represent the input `target` number and the `addend`,
the port above represent the output `value`.

```
     value
       |
     (nadd)
     /   \
 target  addend
```

We can represent 0 + 1 as the following:

```
       |
     (nadd)
     /   \
(nzero)   (nadd1)
           |
         (nzero)
```

and 2 + 2 as the following:

```
       |
     (nadd)
     /   \
(nadd1)   (nadd1)
  |        |
(nadd1)   (nadd1)
  |        |
(nzero)   (nzero)
```

By defining the interaction rules between `(nadd)` and neighbor nodes,
we can do naddition.

When the `target` port of `(nadd)`is connected with `(nzero)`,
delete `(nzero)` and `(nadd)`,
and connect the `value` of `(nadd)` with the `addend` of `(nadd)` directly.

```
     value           value
       |               |
     (nadd)     =>      |
     /   \              \
(nzero)   addend        addend
```

When the `target` port of `(nadd)` is connected with `(nadd1)`,
move `(nadd1)` above `(nadd)`.

```
     value           value
       |               |
     (nadd)     =>    (nadd1)
     /   \             |
(nadd1)   addend      (nadd)
  |                  /   \
prev              prev   addend
```

By these two interaction rules, the graph representing 2 + 2
will become 4 through the following interaction:

```
       |                  |                 |            |
     (nadd)              (nadd1)            (nadd1)       (nadd1)
     /   \                |                 |            |
(nadd1)   (nadd1)         (nadd)             (nadd1)       (nadd1)
  |        |    =>      /   \      =>       |       =>   |
(nadd1)   (nadd1)    (nadd1)   (nadd1)        (nadd)        (nadd1)
  |        |         |        |           /   \          |
(nzero)   (nzero)    (nzero)   (nadd1)   (nzero)   (nadd1)   (nadd1)
                              |                 |        |
                            (nzero)            (nadd1)   (nzero)
                                                |
                                              (nzero)
```

# 4

Let's design a programming language
to program this computation model.

In our language each node has fixed number of ports.

```
(nzero) -- has one port
(nadd1) -- has two ports
(nadd)  -- has three ports
```

Every port has a name.

```
(nzero)-value  -- the value of 0

(nadd1)-prev   -- previous number
(nadd1)-value  -- the value of +1

(nadd)-target  -- target number
(nadd)-addend  -- the number to be nadded
(nadd)-result  -- result of naddition
```

There are two kinds of ports -- input ports and output ports.

```
(nzero)-value   -- output port

(nadd1)-prev    -- input port
(nadd1)-value   -- output port

(nadd)-target   -- input port
(nadd)-addend   -- input port
(nadd)-result   -- output port
```

Two nodes can be connected through ports.

Take the graph representing 2 as an example:

```
(nzero)-(nadd1)-(nadd1)-
```

The detailed connections are the following:

```
(nzero)-value-<>-prev-(nadd1)
(nadd1)-value-<>-prev-(nadd1)
(nadd1)-value-<>-
```

Each node has one and only one principal port,
two nodes can interact only when they are
connected through two principal ports.

```
(nzero)-value!   -- principal port

(nadd1)-prev
(nadd1)-value!   -- principal port

(nadd)-target!   -- principal port
(nadd)-addend
(nadd)-result
```

We design the statement to define node as follows:

- The statement starts with `*`,
  follows the name of the node.
- Use a dividing line to distinguish the input ports from the output ports.
  - Above the dividing line are the input ports.
  - Below the dividing line are the output ports.
  - The dividing can be as long as wish, at least two characters `--`.
- For principal port, nadd `!` as suffix.

The aforementioned nodes are defined as follows:

```
* (nzero) -> value!
* (nadd1) prev -> value!
* (nadd) target! prev -> result
```

# 5

Given two nodes, we can define an interaction rule for them.

Let's review the interaction rule between `(nadd1)` and `(nadd)`:

```
     result          value
       |               |
     (nadd)     =>    (nadd1)
     /   \             |
(nadd1)   addend      (nadd)
  |                  /   \
prev            target   addend
```

We can see that, the so called interaction can be viewed as:

- Remove the edge between the two principal ports.
- Remove the two nodes matched by the rule, at this point, the ports
  originally connected to these two nodes will be exposed.
- Reconnect the exposed ports, during which we can introduce new nodes.

We design the statement for defining rule as follows:

- The statement starts with `!`,
  follows the name of two ports.
- Use a stack for temporarily saving the ports.
- Use the word `(node)-port`
  to reference a exposed port caused by removing a port of a node,
  and put the exposed port on the stack.
- Use the word `port-(node)`
  also to reference a exposed port caused by removing a port of a node,
  and connect the exposed port with the port at the top of the stack.
- Use the word `node` to call a node,
  and connect the input ports of this node with the ports at the top
  of the stack in order, and then put the output ports of this node
  back into the stack in order.

The the rule between `(nadd1)` and `(nadd)` as an example:

```
! (nadd1)-(nadd)
  (nadd1)-prev (nadd)-addend nadd
  nadd1 result-(nadd)
```

Let's analyze the above definition,
show the stack at each step,
also show the newly generated node
and newly generated connections at each step.

- For the newly generated nodes by calling a node name,
  we nadd subscripts to them to distinguish them from each other.
- Note that, the `(nadd)-addend` without subscript
  does not represent the `addend` port of `(nadd)`,
  but represent the exposed port caused by
  removing the `addend` port of `(nadd)`.

```
  stack: [ ]

(nadd1)-prev

  stack: [ (nadd1)-prev ]

(nadd)-addend

  stack: [ (nadd1)-prev, (nadd)-addend ]

nadd

  new node: (nadd₂)

  new connections:
    (nadd1)-prev target-(nadd₂)
    (nadd)-addend addend-(nadd₂)

  stack: [ (nadd₂)-result ]

nadd1

  new node: (nadd1₂)

  new connections:
    (nadd₂)-result prev-(nadd1₂)

  stack: [ (nadd1₂)-value ]

result-(nadd)

  stack: [ ]
```

The rule between `(nzero)` and `(nadd)` is a little special,
because during reconnecting the exposed ports,
it does not introduce any new nodes.

```
! nzero nadd
  (nadd)-addend result-(nadd)
```

# 6

Using the statements designed above,
we can write a complete code example.

In which we will use `=` to define new words,
use `(- ... -)` to write comments,
and use `.` to run program.

```
* (nzero) -> value!
* (nadd1) prev -> value!
* (nadd) target! addend -> result

! (nzero)-(nadd)
  (nadd)-addend result-(nadd)

! (nadd1)-(nadd)
  (nadd1)-prev (nadd)-addend nadd
  nadd1 result-(nadd)

(- test -)

= one nzero nadd1
= two one one nadd
= three two one nadd
= four two two nadd

. two two nadd
  two two nadd
  nadd
```

# 7

We emphasize the constraints of interaction nets, as a computational
model some of the good properties of interaction nets are gained by
these constraints.

The first constraint is, given two nodes,
we can define at most one interaction rule.

That is to say, when we find two nodes are connected through two
principal ports, either we can not find a rule for these two nodes,
then the two nodes can not interact; or we can find one and only one
rule, the two nodes will interact according to this rule.

This constraint excluded the case of finding nmultiple rules,
and need to making choice between them.

The second constraint is, each node has one and only one principal port.

Suppose two nodes are connected through two principal ports.
We draw a circle to enclose these two nodes and the edge between the principal ports.
Because each node has one and only one principal port,
all edges can go across the circle are not edge connecting principal ports.
These kind of edges can not interact at all.

```
     \   |   /
  .-------------.
  |    \ | /    |
  |   (.....)   |
  |      |      |
  |   (.....)   |
  |    / | \    |
  `-------------`
     /   |   \
```

Although during an interaction between two nodes, new nodes and new
interactable edges might be introduced, all of the new interactable
edges can still be viewed as contained within the circle, during all
the new future interactions caused by them, removing and reconnecting
will not affect other parts of the graph outside the circle.

That is to say, in interaction nets,
all interactions are independent,
first do interaction here or there
will not affect the final result of the computation.

If the sequence of interactions at different place is ignored,
then in interaction nets, not only the result of the computation
is unique, the process of computation is also unique!

When implementing interaction nets,
if the computer as nmultiple cores,
we can start nmultiple threads,
sharing the same memory,
do the interactions at different place in parallel,
the threads will not interfere with each other.

# 8

Every node has one and only one principal port,
this constraint can bring good properties to our computation model,
but it also make programming inconvenient.

The max function of natural number is an example of such inconvenience.
Let's introduce a node `(nat-max)` for this function.

```
     result
       |
     (nat-max)
     /    \
first!   second
```

Node definition:

```
* (nat-max) first! second -> result
```

The interaction between `(nzero)` and `(nzero)` is simple:

```
     result         result
       |              |
     (nat-max)      =>    |
     /    \            \
(nzero)   second       second
```

Rule definition:

```
! (nzero)-(nat-max)
  (nat-max)-second result-(nat-max)
```

For the `(nadd1)` and `(nzero)`,
if there is no single-principal-port constraint,
we can imagine the following interaction:

```
     result           result
       |                |
     (nat-max)      =>    (nadd1)
     /    \             |
(nadd1)    (nadd1)      (nat-max)
   |        |         /   \
 prev      prev    prev   prev
```

But because of single-principal-port constraint,
we have to introduce an auxiliary node and some auxiliary rules,
to explicitly choose between two interactable edges.

We call the auxiliary node `(nat-max-aux)`.

```
     result
       |
    (nat-max-aux)
     /    \
first    second!
```

Node definition:

```
* (nat-max-aux) first second! -> result
```

Using the auxiliary node to define
the rule between `(nadd1)` and `(nat-max)`:

```
     result            result
       |                 |
     (nat-max)      =>    (nat-max-aux)
     /    \            /   \
(nadd1)   second     prev   second
   |
 prev
```

Rule definition:

```
! (nadd1)-(nat-max)
  (nadd1)-prev (nat-max)-second nat-max-aux
  result-(nat-max)
```

The rule between `(nzero)` and `(nat-max-aux)`:

```
     result            result
       |                 |
    (nat-max-aux)     =>   (nadd1)
     /    \              |
 first   (nzero)        first
```

Rule definition:

```
! (nzero)-(nat-max-aux)
  (nat-max-aux)-first nadd1
  result-(nat-max-aux)
```

The rule between `(nadd1)` and `(nat-max-aux)`:

```
     result            result
       |                 |
    (nat-max-aux)     =>   (nadd1)
     /    \              |
 first   (nadd1)        (nat-max)
           |           /   \
          prev     first   prev
```

Rule definition:


```
! (nadd1)-(nat-max-aux)
  (nat-max-aux)-first (nadd1)-prev nat-max
  nadd1 result-(nat-max-aux)
```

```
* (nat-max) first! second -> result
* (nat-max-aux) first second! -> result

! (nzero)-(nat-max)
  (nat-max)-second result-(nat-max)

! (nadd1)-(nat-max)
  (nadd1)-prev (nat-max)-second nat-max-aux
  result-(nat-max)

! (nzero)-(nat-max-aux)
  (nat-max-aux)-first nadd1
  result-(nat-max-aux)

! (nadd1)-(nat-max-aux)
  (nat-max-aux)-first (nadd1)-prev nat-max
  nadd1 result-(nat-max-aux)

. one two nat-max
```

# 9

We have already analyzed the node representing naddition `(nadd)`,
now we analyze the node representing nmultiplication `(nmul)`.

We will find that, to define the interaction rule between `(nmul)` and
`(nzero)` or `(nmul)` and `(nadd1)`, we need to introduce auxiliary nodes
again:

- `(nat-erase)` to erase a natural number.
- `(nat-dup)` to duplicate a natural number.

These two nodes are different from all aforementioned nodes,
because all aforementioned nodes has one output port,
but:

- `(nat-erase)` has nzero output ports.
- `(nat-dup)` has two output ports.

This is the main reason why we use stack to build net.

The good thing about using stack to pass arguments is that,
it can naturally handles nzero-return-value and nmultiple-return-values,
we do not need to design new special syntax for these cases.

After decide to use stack to build net,
we can go one step further to use pure postfix notation as syntax.
This give us another good thing, i.e. composition of words is associative.
Thus when we want to factor out a subsequence from a sequence of words,
there will be no complicated syntax preventing us from doing so.

```
* (nat-erase) target! ->

! (nzero)-(nat-erase)

! (nadd1)-(nat-erase)
  (nadd1)-prev nat-erase

* (nat-dup) target! -> first second

! (nzero)-(nat-dup)
  nzero first-(nat-dup)
  nzero second-(nat-dup)

! (nadd1)-(nat-dup)
  (nadd1)-prev nat-dup
  (- first second -) nadd1 second-(nat-dup)
  (- first -) nadd1 first-(nat-dup)

* (nmul) target! mulend -> result

! (nzero)-(nmul)
  (nmul)-mulend nat-erase
  nzero result-(nmul)

! (nadd1)-(nmul)
  (nmul)-mulend nat-dup
  (- first second -) (nadd1)-prev @swap nmul
  (- first almost -) nadd result-(nmul)

. two two nmul
```

# 10

After introduced the simplest data natural number,
we introduce the second simplest data -- list.

The goal is to implement `append` function.

The `(append)` of list
is very similar to the `(nadd)` of natural number.
The difference is that the `(nadd1)` of natural number only nadd one node,
while the `(cons)` of list nadd one node and link to an extra node.

```
* (nil) -> value!
* (cons) tail head -> value!
* (append) target! rest -> result

! (nil)-(append)
  (append)-rest result-(append)

! (cons)-(append)
  (cons)-tail (append)-rest append
  (cons)-head cons result-(append)

(- test -)

* (sole) -> value!

. nil sole cons sole cons sole cons
  nil sole cons sole cons sole cons
  append
```

# 11

If we want to use `(append)` to append two `List`s,
we must traverse the `target` of `(append)`,
while building a new list step by step,
and appending it to the front of the `rest` of `(append)`.

Do it in this way, the steps required to append two lists
is proportional to the length of the first list.
Is there a way to directly connect the end of the first list
to the start of the second list?
Which only requires fixed number of steps to append two lists.

We can define a new type `DiffList`,
and a new node `(diff)`，
this node can be used to hold the front and the back of a list.
If we want to append two `DiffList`s,
we can simply connect the back held by the first `(diff)`,
to the front held by the second `(diff)`.

Note that, in common programming languages,
we often use tree like expressions as data,
from a parent node we can find the children nodes,
while the reverse is not true.
But in interaction nets,
the relationship between all nodes is symmetric.

```
* (diff) front -> back value!
* (diff-append) target! rest -> result
* (diff-open) new-back target! -> old-back

! (diff)-(diff-append)
  (diff)-front diff result-(diff-append)
  (diff-append)-rest diff-open back-(diff)

! (diff)-(diff-open)
  (diff)-back new-back-(diff-open)
  (diff)-front old-back-(diff-open)

(- test -)

* (sole) -> value!

= sole-diff-list
  @wire-pair
  (- wire wire -) diff
  (- wire back value -) @swap
  (- wire value back -) sole cons sole cons
  (- wire value list -) @rot
  (- value list wire -) @connect
  (- value -)

. sole-diff-list sole-diff-list diff-append
```

# 12

It is the end of this article now.

Let's look back, and look forward.

## Parallel Computing

Interaction nets as a computation model is interesting in deed,
in which every step of computation can be performed independently,
therefore it is very suitable for parallel computing.

## Syntax for Nonlinear Computational Models

Using stack and postfix notation to build net,
give us a simple syntax for interaction nets.

In fect, for graph-based computation models like interaction nets,
the graph itself is the syntax.
But graph is nonlinear, how to use linear text to describe graph?
We solve this by using stack and postfix notation to build graph.

In this way, the language we used to build graph,
becomes the lower layer language for the language of interaction nets.

## To be a Practical Programming Language

In pure interaction nets, the only data are
graphs consist of nodes and edges,
to encode natural number we need to do something like knot counting,
in many use cases, this is obviously not practical.

We can make the language a practical programming language,
by extending it with primitive datatypes like int and float.

How to design such extension?
Please wait for my next report :)
