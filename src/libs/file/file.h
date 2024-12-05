#pragma once

typedef FILE file_t;

bool file_exists(const char *file_name);
file_t *file_open_or_fail(
    const char *file_name,
    const char *mode);
off_t file_size(file_t *file);
char *file_read_text(file_t *file);
uint8_t *file_read_bytes(file_t *file);
