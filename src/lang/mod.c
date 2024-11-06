#include "index.h"

// A mod is a compilation unit,
// which stores compiled rules.

struct _mod_t {
    list_t *node_definition_list;
};
