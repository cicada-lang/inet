#include "index.h"

// The free ports in a frame can be referenced by `op_fpt_t`.

struct frame_t {
    size_t program_counter;
    const program_t *program;
    free_port_group_t *first_free_port_group;
    free_port_group_t *second_free_port_group;
};

frame_t *
frame_new(const program_t *program) {
    frame_t *self = allocate(sizeof(frame_t));
    self->program_counter = 0;
    self->program = program;
    // self->first_free_port_group;
    // self->second_free_port_group;
    return self;
}
