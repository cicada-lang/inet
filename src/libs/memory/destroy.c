#include "index.h"

void
destroy(void **item_pointer) {
    assert(item_pointer);
    if (*item_pointer) {
        void *item = *item_pointer;
        free(item);
        *item_pointer = NULL;
    }
}
