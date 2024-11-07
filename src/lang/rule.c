#include "index.h"

struct rule_t {
    const node_definition_t *first_node_definition;
    const node_definition_t *second_node_definition;
    const program_t *program;
};
