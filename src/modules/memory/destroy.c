#include "index.h"

void
destroy(void **value_pointer) {
    assert(value_pointer);
    if (*value_pointer) {
        void *value = *value_pointer;
        free(value);
        *value_pointer = NULL;
    }
}
