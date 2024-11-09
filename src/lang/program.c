#include "index.h"

struct program_t {
    list_t *op_list;
};

program_t *
program_new(void) {
    program_t *self = allocate(sizeof(program_t));
    self->op_list = list_new();
    list_set_item_destructor(self->op_list, (list_item_destructor_t *) op_destroy);
    return self;
}

void
program_destroy(program_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        program_t *self = *self_pointer;
        list_destroy(&self->op_list);
        free(self);
        *self_pointer = NULL;
    }
}
