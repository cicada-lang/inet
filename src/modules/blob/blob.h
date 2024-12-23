#pragma once

blob_t *blob_new(size_t size);
void blob_destroy(blob_t **self_pointer);

size_t blob_size(const blob_t *self);
uint8_t *blob_bytes(const blob_t *self);
char *blob_string(const blob_t *self);

void blob_copy_from(blob_t *self, const uint8_t *bytes);
void blob_copy_into(const blob_t *self, uint8_t *bytes);

bool blob_equal(blob_t *left, blob_t *right);
blob_t *blob_copy(blob_t *self);
