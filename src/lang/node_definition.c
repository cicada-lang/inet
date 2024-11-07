#include "index.h"

struct node_definition_t {
    const definition_tag_t tag;
    const char *name;
    const size_t input_arity;
    const size_t output_arity;
    port_definition_t *port_definition_array;
};

struct port_definition_t {
    const char *name;
    const bool is_principal;
};
