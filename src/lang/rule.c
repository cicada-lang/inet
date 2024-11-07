#include "index.h"

struct rule_t {
    const node_spec_t *first_node_spec;
    const node_spec_t *second_node_spec;
    const program_t *program;
};
