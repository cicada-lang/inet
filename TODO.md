net -- 也许可以直接实现成内存管理的 arena

- a heap of ports (no need nodes)
- a stack of active edges

mod -- mod_t -- has node_definition_list

- 构造 net 的时候需要用到 mod，但是运行的时候不需要用到 mod，是这样吗？

rule -- rule_t

- 如何设计 rule 这种 "double names as key" 的 kv store？

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?
