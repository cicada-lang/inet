#include "index.h"

active_pair_t *active_pair_new(void) {
    active_pair_t *self = allocate(sizeof(active_pair_t));
    return self;
}

void
active_pair_destroy(active_pair_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        active_pair_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}
