#include "index.h"

// A mod is a compilation unit,
// like the dictionary of forth,
// which stores definitions.

struct mod_t {
    list_t *node_definition_list;
};
