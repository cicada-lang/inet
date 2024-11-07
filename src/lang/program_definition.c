#include "index.h"

struct program_definition {
    definition_tag_t tag;
    char *name;
    program_t *program;
};
