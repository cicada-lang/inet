#pragma once

typedef FILE file_t;

file_t *file_open_or_fail(
    const char *file_name,
    const char *mode,
    const char *message);
char *file_read(file_t *file);
