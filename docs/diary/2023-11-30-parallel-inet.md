---
title: Parallel iNet
date: 2023-11-30
---

# Problem

To implement parallel interaction nets,
we need to let many threads share the same memory.

To allocate memory of cells of the same size,
we can use an array, and a stack of unused indexes
(let's call this free-stack).

But the stack will still be the part where multi-thread is not safe
right?  If any part of the implementation is not lock-free, the fine
grain parallel advantage of inet might be lost.

# Solution A

Maybe i can just use 8 "free-stacks" for 8 threads.

When a used index is to be freed, i can see which thread is having the
least free indexes, and give the new freed index to it.

And a "free-stack" can be viewed as a ring, i give back to the front
instead of the end, thus lock-free.

The query about "the least free indexes" is just heuristic, thus also
lock-free.

# Datatypes

I need to allocate the following kinds of datatypes:

```
Node {
  definition: NodeDefinition
  ports: List<Port>
}

Port {
  node: Node
  halfEdge?: HalfEdge
}

HalfEdge {
  otherHalfEdge: HalfEdge
  port?: Port
}
```
