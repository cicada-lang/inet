#include "index.h"

void *
allocate(size_t size) {
    void *bytes = calloc(1, size);
    assert(bytes);
    return bytes;
}

void *
allocate_many(size_t size, size_t unit_size) {
    void *many = calloc(size, unit_size);
    assert(many);
    return many;
}

void *
allocate_pointers(size_t size) {
    return allocate_many(size, sizeof(void *));
}
