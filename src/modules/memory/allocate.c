#include "index.h"

static bool
is_16_byte_aligned(void *address) {
    return (((uintptr_t) address) & ((uintptr_t) 0xf)) == 0;
}

void *
allocate(size_t size) {
    void *address = calloc(1, size);
    assert(address);
    assert(is_16_byte_aligned(address));
    return address;
}

void *
allocate_many(size_t size, size_t unit_size) {
    void *address = calloc(size, unit_size);
    assert(address);
    assert(is_16_byte_aligned(address));
    return address;
}

void *
allocate_pointers(size_t size) {
    return allocate_many(size, sizeof(void *));
}
