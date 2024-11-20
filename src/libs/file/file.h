#pragma once

#define _POSIX_SOURCE 1

typedef FILE file_t;

file_t *file_open_or_fail(
    const char *file_name,
    const char *mode,
    const char *message);
char *file_read(file_t *file);
off_t file_size(file_t *file);
