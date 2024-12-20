#include "index.h"

// The address of a block returned by malloc or realloc in GNU systems
// is always a multiple of eight (or sixteen on 64-bit systems).
// -- https://www.gnu.org/software/libc/manual/html_node/Aligned-Memory-Blocks.html

bool
pointer_is_8_bytes_aligned(void *pointer) {
    return (((uintptr_t) pointer) & ((uintptr_t) 0x7)) == 0;
}

void *
allocate(size_t size) {
    void *pointer = calloc(1, size);
    assert(pointer);
    assert(pointer_is_8_bytes_aligned(pointer));
    return pointer;
}

void *
allocate_many(size_t size, size_t unit_size) {
    void *pointer = calloc(size, unit_size);
    assert(pointer);
    assert(pointer_is_8_bytes_aligned(pointer));
    return pointer;
}

void *
allocate_pointers(size_t size) {
    return allocate_many(size, sizeof(void *));
}
