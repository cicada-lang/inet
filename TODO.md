node_definition_t -- with port_definition_t
- 是否应该用 definition 这个后缀？
- sign_t sign;
- bool is_principal;
port_t -- has node_definition
rule_t

# design

re-design syntax to simplify diff-list.test.inet
- remove the idea of `(diff) @spread`
- how about `@connect`?
