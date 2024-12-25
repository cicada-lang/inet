#include "index.h"

bool
is_xnull(value_t value) {
    return value == xnull;
}

void *
to_null(value_t value) {
    assert(is_xnull(value));
    return NULL;
}
