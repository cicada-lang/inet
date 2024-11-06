net_t -- port_id_t for virtual address
net_t -- has port_heap
net_t -- has active_edge_stack

mod -- mod_t -- has node_definition_list

- 一个 mod 是一个 compilation unit
- 构造 net 的时候需要用到 mod，但是运行的时候不需要用到 mod，是这样吗？

rule -- rule_t

- 如何设计 rule 这种 "double names as key" 的 kv store？

# design

re-design syntax to simplify diff-list.test.inet

- remove the idea of `(diff) @spread`
- how about `@connect`?
