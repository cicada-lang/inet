#include "index.h"

void *allocate(size_t size) {
    void *bytes = calloc(1, size);
    assert(bytes);
    return bytes;
}

void *allocate_array(size_t size, size_t unit_size) {
    void *array = calloc(size, unit_size);
    assert(array);
    return array;
}
