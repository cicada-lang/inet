#include "index.h"

struct node_definition_t {
    char *name;
    size_t input_arity;
    size_t output_arity;
    port_definition_t *port_definition_array;
};

struct port_definition_t {
    char *name;
    bool is_principal;
};
