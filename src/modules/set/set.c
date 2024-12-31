#include "index.h"

struct set_t {
    hash_t *value_hash;
};

set_t *
set_new(void) {
    set_t *self = new(set_t);
    self->value_hash = hash_new();
    return self;
}

void
set_destroy(set_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        set_t *self = *self_pointer;
        hash_destroy(&self->value_hash);
        free(self);
        *self_pointer = NULL;
    }
}
