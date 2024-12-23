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
blob_size(const blob_t *self) {
    return self->size;
}

uint8_t *
blob_bytes(const blob_t *self) {
    return self->bytes;
}

char *
blob_string(const blob_t *self) {
    return (char *) self->bytes;
}

void
blob_copy_from(blob_t *self, const uint8_t *bytes) {
    memcpy(self->bytes, bytes, self->size);
}

void
blob_copy_into(const blob_t *self, uint8_t *bytes) {
    memcpy(bytes, self->bytes, self->size);
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
blob_copy(blob_t *self) {
    blob_t *blob = blob_new(self->size);
    memcpy(blob->bytes, self->bytes, self->size);
    return blob;
}
