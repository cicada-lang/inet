#include "index.h"

// The free ports in a frame can be referenced by `op_fpt_t`.

struct frame_t {
    size_t index;
    const program_t *program;
    free_port_group_t *first_free_port_group;
    free_port_group_t *second_free_port_group;
};
