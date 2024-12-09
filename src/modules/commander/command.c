#include "index.h"

command_t *
command_new(const char *name) {
    command_t *self = new(command_t);
    self->name = name;
    self->description = NULL;
    self->help = NULL;
    self->run = NULL;
    return self;
}

void
command_destroy(command_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        free(*self_pointer);
        *self_pointer = NULL;
    }
}
