#include "index.h"

struct program_t {
    list_t *op_list;
};

program_t *
program_new(void) {
    program_t *self = allocate(sizeof(program_t));
    return self;
}
