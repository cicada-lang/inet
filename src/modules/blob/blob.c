#include "index.h"

// with an extra ending '\0' to be viewed as string.

struct blob_t {
    size_t size;
    uint8_t *bytes;
};

blob_t *
blob_new(size_t size) {
    blob_t *self = new(blob_t);
    self->size = size;
    self->bytes = allocate(size + 1);
    return self;
}

void
blob_destroy(blob_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        blob_t *self = *self_pointer;
        free(self->bytes);
        free(self);
        *self_pointer = NULL;
    }
}

size_t
blob_size(blob_t *self) {
    return self->size;
}

uint8_t *
blob_bytes(blob_t *self) {
    return self->bytes;
}

char *
blob_string(blob_t *self) {
    return (char *) self->bytes;
}

bool
blob_equal(blob_t *left, blob_t *right) {
    if (left == right)
        return true;

    if (left->size != right->size)
        return false;

    return memcmp(
        left->bytes,
        right->bytes,
        left->size) == 0;
}

blob_t *
blob_dup(blob_t *self) {
    blob_t *blob = blob_new(self->size);
    memcpy(blob->bytes, self->bytes, self->size);
    return blob;
}
