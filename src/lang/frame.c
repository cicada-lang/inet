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
    return self;
}

void
frame_destroy(frame_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        frame_t *self = *self_pointer;
        free_port_group_destroy(&self->first_free_port_group);
        free_port_group_destroy(&self->second_free_port_group);
        free(self);
        *self_pointer = NULL;
    }
}
