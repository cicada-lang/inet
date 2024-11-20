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
to practice this computation model.

# 2

How to use graph to encode data?

Suppose we want to encode the simplest data -- natural number.
We can mimic the ancient knot counting, using node to do the counting.

```
0  (zero)--
1  (zero)--(add1)--
2  (zero)--(add1)--(add1)--
3  (zero)--(add1)--(add1)--(add1)--
```

The node representing 0 `(zero)` has one port,
the node representing +1 `(add1)` has two ports,
we can encode natural number
by connecting these nodes through the ports.

# 3

How to use graph to represent functions that operate on natural numbers?

Take addition as an example, we need to introduce a new node to represent addition,
and to define interaction rules between this node and other nodes.

We use a node with three ports to represent addition.

```
       |
     (add)
     /   \
```

The two ports below represent the input `target` number and the `addend`,
the port above represent the output `value`.

```
     value
       |
     (add)
     /   \
 target  addend
```

We can represent 0 + 1 as the following:

```
       |
     (add)
     /   \
(zero)   (add1)
           |
         (zero)
```

and 2 + 2 as the following:

```
       |
     (add)
     /   \
(add1)   (add1)
  |        |
(add1)   (add1)
  |        |
(zero)   (zero)
```

By defining the interaction rules between `(add)` and neighbor nodes,
we can do addition.

When the `target` port of `(add)`is connected with `(zero)`,
delete `(zero)` and `(add)`,
and connect the `value` of `(add)` with the `addend` of `(add)` directly.

```
     value           value
       |               |
     (add)     =>      |
     /   \              \
(zero)   addend        addend
```

When the `target` port of `(add)` is connected with `(add1)`,
move `(add1)` above `(add)`.

```
     value           value
       |               |
     (add)     =>    (add1)
     /   \             |
(add1)   addend      (add)
  |                  /   \
prev              prev   addend
```

By these two interaction rules, the graph representing 2 + 2
will become 4 through the following interaction:

```
       |                  |                 |            |
     (add)              (add1)            (add1)       (add1)
     /   \                |                 |            |
(add1)   (add1)         (add)             (add1)       (add1)
  |        |    =>      /   \      =>       |       =>   |
(add1)   (add1)    (add1)   (add1)        (add)        (add1)
  |        |         |        |           /   \          |
(zero)   (zero)    (zero)   (add1)   (zero)   (add1)   (add1)
                              |                 |        |
                            (zero)            (add1)   (zero)
                                                |
                                              (zero)
```

# 4

Let's design a programming language
to practice this computation model.

In our language each node has fixed number of ports.

```
(zero) // has one port
(add1) // has two ports
(add)  // has three ports
```

Every port has a name.

```
(zero)-value  // the value of 0

(add1)-prev   // previous number
(add1)-value  // the value of +1

(add)-target  // target number
(add)-addend  // the number to be added
(add)-result  // result of addition
```

There are two kinds of ports -- input ports and output ports.

```
-------------
(zero)-value   // output port

(add1)-prev    // input port
-------------
(add1)-value   // output port

(add)-target   // input port
(add)-addend   // input port
-------------
(add)-result   // output port
```

Two nodes can be connected through ports,
an input port must be connected to an output port.

Take the graph representing 2 as an example:

```
(zero)--(add1)--(add1)--
```

The detailed connections are the following:

```
(zero)-value prev-(add1)
(add1)-value prev-(add1)
(add1)-value // not yet connected free port
```

Each node has one and only one principal port,
two nodes can interact only when they are
connected through two principal ports.

```
-------------
(zero)-value!   // principal port

(add1)-prev
-------------
(add1)-value!   // principal port

(add)-target!   // principal port
(add)-addend
-------------
(add)-result
```

We also require each port to have a specific type,
and only ports with matching types can be connected.

We design the statement to define node as follows:

- The statement starts with `node`,
  follows the name of the node,
  ends with `end`.
- Use a dividing line to distinguish the input ports from the output ports.
  - Above the dividing line are the input ports.
  - Below the dividing line are the output ports.
  - The dividing can be as long as wish, at least two characters `--`.
- The name of a port is written after the type as a label.
- For principal port, add `!` as suffix.

Suppose the type representing natural number is `Nat`,
the aforementioned nodes are defined as follows:

```
node zero
  --------
  Nat :value!
end

node add1
  Nat :prev
  --------
  Nat :value!
end

node add
  Nat :target!
  Nat :prev
  --------
  Nat :result
end
```

# 5

A type might have other types as arguments.

For now, the only information we need is the number of input arguments,
because the type of an argument must be a type,
and the number of output arguments must be one.

But to be consistent with the definition of node,
we design the statement to define type as follows:

- The statement starts with `type`,
  follows the name of the type,
  ends with `end`.
- Use a dividing line to distinguish the input type arguments from the output type arguments.
  - Above the dividing line are the input type arguments (must be `Type`).
  - Below the dividing line are the output type arguments, (must be one `Type`).
  - The dividing can be as long as wish, at least two characters `--`.
  - `Type` is a built-in value, we reference it by `@Type`.
    - All built-in definitions will use `@` as prefix.

Take the type representing natural number `Nat` as an example, it has no input type arguments, thus it's definition is:

```
type Nat -- @Type end
```

Take `List` as another example, it has one input type argument, i.e. the element type, thus it's definition is:

```
type List @Type -- @Type end
```

# 6

Given two nodes, we can define an interaction rule for them.

Let's review the interaction rule between `(add1)` and `(add)`:

```
     result          value
       |               |
     (add)     =>    (add1)
     /   \             |
(add1)   addend      (add)
  |                  /   \
prev            target   addend
```

We can see that, the so called interaction can be viewed as:

- Remove the edge between the two principal ports.
- Remove the two nodes matched by the rule, at this point, the ports
  originally connected to these two nodes will be exposed.
- Reconnect the exposed ports, during which we can introduce new nodes.

We design the statement for defining rule as follows:

- The statement starts with `rule`,
  follows the name of two ports,
  ends with `end`.
- Use a stack for temporarily saving the ports.
- Use the word `(node)-port`
  to reference a exposed port caused by removing a port of a node,
  and put the exposed port on the stack.
- Use the word `port-(node)`
  also to reference a exposed port caused by removing a port of a node,
  and connect the exposed port with the port at the top of the stack.
- Use the word `(node)` to call a node,
  and connect the input ports of this node with the ports at the top
  of the stack in order, each input port will use up a port in the
  stack, and then put the output ports of this node back into the
  stack in order.

The the rule between `(add1)` and `(add)` as an example:

```
rule add1 add
  (add)-addend
  (add1)-prev add
  add1 result-(add)
end
```

Let's analyze the above definition,
show the stack at each step,
also show the newly generated node
and newly generated connections at each step.

- For the newly generated nodes by calling a node name,
  we add subscripts to them to distinguish them from each other.
- Note that, the `(add)-addend` without subscript
  does not represent the `addend` port of `(add)`,
  but represent the exposed port caused by
  removing the `addend` port of `(add)`.

```
  stack: [ ]

(add)-addend

  stack: [ (add)-addend ]

(add1)-prev

  stack: [ (add)-addend, (add1)-prev ]

add

  new node: (add₂)

  new connections:
    (add1)-prev target-(add₂)
    (add)-addend addend-(add₂)

  stack: [ (add₂)-result ]

add1

  new node: (add1₂)

  new connections:
    (add₂)-result prev-(add1₂)

  stack: [ (add1₂)-value ]

result-(add)

  stack: [ ]
```

The rule between `(zero)` and `(add)` is a little special,
because during reconnecting the exposed ports,
it does not introduce any new nodes.

```
rule zero add
  (add)-addend
  result-(add)
end
```

# 7

Using the statements designed above,
we can write a complete code example.

In which we will use `define` to define new words,
and before using `define` to define a new word,
we must use `claim` to claim the type of the word.

```
type Nat -- @Type end

node zero
  ------------
  Nat :value!
end

node add1
  Nat :prev
  ------------
  Nat :value!
end

node add
  Nat :target!
  Nat :addend
  ------------
  Nat :result
end

rule zero add
  (add)-addend
  result-(add)
end

rule add1 add
  (add)-addend
  (add1)-prev add
  add1 result-(add)
end

claim one -- Nat end

define one
  zero add1
end

claim two -- Nat end

define two
  one add1
end

claim add2 Nat -- Nat end

define add2
  two add
end

one add2
one add2
add
```

# 8

We emphasize the constraints of interaction nets, as a computational
model some of the good properties of interaction nets are gained by
these constraints.

The first constraint is, given two nodes,
we can define at most one interaction rule.

That is to say, when we find two nodes are connected through two
principal ports, either we can not find a rule for these two nodes,
then the two nodes can not interact; or we can find one and only one
rule, the two nodes will interact according to this rule.

This constraint excluded the case of finding multiple rules,
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
if the computer as multiple cores,
we can start multiple threads,
sharing the same memory,
do the interactions at different place in parallel,
the threads will not interfere with each other.

# 9

Every node has one and only one principal port,
this constraint can bring good properties to our computation model,
but it also make programming inconvenient.

The max function of natural number is an example of such inconvenience.
Let's introduce a node `(max)` for this function.

```
     result
       |
     (max)
     /    \
first!   second
```

Node definition:

```
node max
  Nat :first!
  Nat :second
  ----------
  Nat :result
end
```

The interaction between `(zero)` and `(zero)` is simple:

```
     result         result
       |              |
     (max)      =>    |
     /    \            \
(zero)   second       second
```

Rule definition:

```
rule zero max
  (max)-second result-(max)
end
```

For the `(add1)` and `(zero)`,
if there is no single-principal-port constraint,
we can imagine the following interaction:

```
     result           result
       |                |
     (max)      =>    (add1)
     /    \             |
(add1)    (add1)      (max)
   |        |         /   \
 prev      prev    prev   prev
```

But because of single-principal-port constraint,
we have to introduce an auxiliary node and some auxiliary rules,
to explicitly choose between two interactable edges.

We call the auxiliary node `(maxAux)`.

```
     result
       |
    (maxAux)
     /    \
first    second!
```

Node definition:

```
node maxAux
  Nat :first
  Nat :second!
  --------
  Nat :result
end
```

Using the auxiliary node to define
the rule between `(add1)` and `(max)`:

```
     result            result
       |                 |
     (max)      =>    (maxAux)
     /    \            /   \
(add1)   second     prev   second
   |
 prev
```

Rule definition:

```
rule add1 max
  (max)-second
  (add1)-prev maxAux
  result-(max)
end
```

The rule between `(zero)` and `(maxAux)`:

```
     result            result
       |                 |
    (maxAux)     =>    (add1)
     /    \              |
 first   (zero)        first
```

Rule definition:

```
rule zero maxAux
  (maxAux)-first add1
  result-(maxAux)
end
```

The rule between `(add1)` and `(maxAux)`:

```
     result            result
       |                 |
    (maxAux)     =>    (add1)
     /    \              |
 first   (add1)        (max)
           |           /   \
          prev     first   prev
```

Rule definition:

```
rule add1 maxAux
  (add1)-prev
  (maxAux)-first max
  add1 result-(maxAux)
end
```

```
type Nat -- @Type end

node zero
  ------
  Nat :value!
end

node add1
  Nat :prev
  ----------
  Nat :value!
end

node maxAux
  Nat :first
  Nat :second!
  --------
  Nat :result
end

node max
  Nat :first!
  Nat :second
  ----------
  Nat :result
end

rule zero max
  (max)-second result-(max)
end

rule add1 max
  (max)-second (add1)-prev maxAux
  result-(max)
end

rule zero maxAux
  (maxAux)-first add1
  result-(maxAux)
end

rule add1 maxAux
  (add1)-prev (maxAux)-first max
  add1 result-(maxAux)
end

claim one -- Nat end
define one zero add1 end

claim two -- Nat end
define two one add1 end

claim three -- Nat end
define three two add1 end

claim four -- Nat end
define four three add1 end

zero two max

three two max
```

# 10

We have already analyzed the node representing addition `(add)`,
now we analyze the node representing multiplication `(mul)`.

We will find that, to define the interaction rule between `(mul)` and
`(zero)` or `(mul)` and `(add1)`, we need to introduce auxiliary nodes
again:

- `(natErase)` to erase a natural number.
- `(natDup)` to duplicate a natural number.

These two nodes are different from all aforementioned nodes,
because all aforementioned nodes has one output port,
but:

- `(natErase)` has zero output ports.
- `(natDup)` has two output ports.

This is the main reason why we use stack to build net.

The good thing about using stack to pass arguments is that,
it can naturally handles zero-return-value and multiple-return-values,
we do not need to design new special syntax for these cases.

After decide to use stack to build net,
we can go one step further to use pure postfix notation as syntax.
This give us another good thing, i.e. composition of words is associative.
Thus when we want to factor out a subsequence from a sequence of words,
there will be no complicated syntax preventing us from doing so.

In the following code, we will use a syntax keyword `import`,
to import definitions from other module.

- One file corresponds to one module.
- Use `.i` as file extension.
- We can use full URL `https//...` to specify a file.
- We can also use relative path `./...` to specify a file.

We will also use a new word `$local`
to save the value at the top of the stack
to a local variable named `local`.

- After saving a value to `$local`,
  we can fetch the value back to the stack
  by calling `local`.
- After the fetching, `$local` will be empty again,
  and can be used to save other value.

```
import
  Nat, zero, add1, add,
  one, two, three,
from "https://code-of-inet-cute.xieyuheng.com/examples/datatypes/Nat.i"

node natErase
  Nat :target!
  --------
end

rule zero natErase end

rule add1 natErase
  (add1)-prev natErase
end

node natDup
  Nat :target!
  --------
  Nat :second
  Nat :first
end

rule zero natDup
  zero first-(natDup)
  zero second-(natDup)
end

rule add1 natDup
  (add1)-prev natDup $first $second
  first add1 first-(natDup)
  second add1 second-(natDup)
end

node mul
  Nat :target!
  Nat :mulend
  --------
  Nat :result
end

rule zero mul
  (mul)-mulend natErase
  zero result-(mul)
end

rule add1 mul
  (mul)-mulend natDup $first $second
  (add1)-prev first mul second add
  result-(mul)
end

two natDup $first $second

two two mul

three three mul
```

# 11

After introduced the simplest data `Nat`,
we introduce the second simplest data -- `List`.

The goal is to implement `append` function.

The `(append)` of `List`
is very similar to the `(add)` of `Nat`.
The difference is that the `(add1)` of `Nat` only add one node,
while the `(cons)` of `List` add one node and link to an extra node.

In the following code, we will use a new word `'A`.

- `'A` will add the symbol of `A` to the stack.
- `'A` can be used as type variable.
- Type variable can be used as type argument, for example `'A List`.

When defining `(cons)` and `(append)`,
the same symbol `'A` occured many times
to representing a type variable.
This means when connecting the corresponding ports,
this type variable must match the same type.

```
type List @Type -- @Type end

node null
  --------
  'A List :value!
end

node cons
  'A :head
  'A List :tail
  --------
  'A List :value!
end

node append
  'A List :target!
  'A List :rest
  --------
  'A List :result
end

rule null append
  (append)-rest
  result-(append)
end

rule cons append
  (append)-rest (cons)-tail append
  (cons)-head cons
  result-(append)
end

import zero from "https://code-of-inet-cute.xieyuheng.com/examples/datatypes/Nat.i"

null zero cons zero cons
null zero cons zero cons
append

null zero cons zero cons
null zero cons zero cons
append @run $result
```

# 12

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

In the following code,
we use `(diff)` to create a new node and return it to the stack,
follows `@spread` to put all it's ports to the stack
in reverse order of the definition,
then we save the ports to local variables for later use.

```
import List from "https://code-of-inet-cute.xieyuheng.com/examples/datatypes/List.i"

type DiffList @Type -- @Type end

node diff
  'A List :front
  -------
  'A List :back
  'A DiffList :value!
end

node diffAppend
  'A DiffList :target!
  'A DiffList :rest
  --------
  'A DiffList :result
end

node diffOpen
  'A DiffList :target!
  'A List :newBack
  ----------
  'A List :oldBack
end

rule diff diffAppend
  (diff)-front diff result-(diffAppend)
  (diffAppend)-rest diffOpen back-(diff)
end

rule diff diffOpen
  (diff)-back newBack-(diffOpen)
  (diff)-front oldBack-(diffOpen)
end

import zero from "https://code-of-inet-cute.xieyuheng.com/examples/datatypes/Nat.i"
import cons from "https://code-of-inet-cute.xieyuheng.com/examples/datatypes/List.i"

(diff) @spread $front $back $value
back zero cons zero cons front @connect value
(diff) @spread $front $back $value
back zero cons zero cons front @connect value
diffAppend

// By using one less local variable `$value`,
// we can simplify the above code:

(diff) @spread $front $back
back zero cons zero cons front @connect
(diff) @spread $front $back
back zero cons zero cons front @connect
diffAppend

// By using one less local variable `$back`,
// we can further simplify the above code:

(diff) @spread $front zero cons zero cons front @connect
(diff) @spread $front zero cons zero cons front @connect
diffAppend

@run $result
```

# 13

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
View this lower layer language as a programming language,
it is also Turing complete.

This idea can not only be used to build graph,
and provide syntax for graph-based computation models,
it can also be used to build more complex nonlinear objects,
such as the generalization of graph theory in high dimensions
-- [Cell complex](https://zh.wikipedia.org/wiki/CW%E5%A4%8D%E5%BD%A2).
If we have a new computation model based on cell complex,
Then the idea of using stacks and postfix notation
to provide syntax for computation model is still applicable.

## Type System

Our language also has a type system,
the process of type checking, is just
the process of runing the lower layer language,
we only need to check weather the types of the two ports
match when connecting the nodes.

In the type system of our language,
the arguments of a type must be type,
but we can also imagine to let the arguments of a type be any value,
to get the so called [dependent type](https://en.wikipedia.org/wiki/Dependent_type).

In this case, it is more difficult for us to judge whether the two
types match, because it needs to judge whether two values ​​that may
contain arbitrary computations are equal.

In common computation models, like Lambda calculus,
it is difficult to implement such judgement,
but in interaction nets, it is relatively easy,
because it is sufficient to judge
whether two pointed graphs are isomorphic
after all the possible interactions in them are finished.

## To be a Practical Programming Language

In pure interaction nets, the only data are
graphs consist of nodes and edges,
to encode natural number we need to do something like knot counting,
in many use cases, this is obviously not practical.

But fortunately, our language already has two layers,
the upper layer is pure interaction nets,
the lower layer is a stack-based postfix notation general programming language.
We can make the whole language a practical programming language,
simply by extending this lower layer language.

How to design such extension?
Please see the report of my next project :)
