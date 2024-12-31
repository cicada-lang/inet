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
