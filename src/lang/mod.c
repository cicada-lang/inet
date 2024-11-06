#include "index.h"

// A mod is a compilation unit,
// which stores compiled rules.

struct mod_t {
    list_t *node_definition_list;
};
