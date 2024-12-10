#pragma once

bool file_exists(const char *file_name);
file_t *file_open_or_fail(const char *file_name, const char *mode);
off_t file_size(file_t *file);

char *file_read_string(file_t *file);

uint8_t *file_read_bytes(file_t *file);
void file_write_bytes(file_t *file, uint8_t *bytes, size_t size);

blob_t *file_read_blob(file_t *file);
void file_write_blob(file_t *file, blob_t *blob);
