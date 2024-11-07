#include "index.h"

struct program_definition {
    const definition_tag_t tag;
    const char *name;
    const program_t *program;
};
