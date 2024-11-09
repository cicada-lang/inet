#include "index.h"

struct node_spec_t {
    const spec_tag_t tag;
    const char *name;
    const size_t input_arity;
    const size_t output_arity;
    port_spec_t *port_spec_array;
};
