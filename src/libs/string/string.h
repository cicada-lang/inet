#pragma once

void string_destroy(char **self_pointer);
char *string_dup(const char *self);
char *string_empty(void);
bool string_equal(const char *left, const char *right);
size_t string_hash(const char *self, size_t size);
bool string_is_int(const char *restrict self);
int64_t string_to_int(const char *self);
bool string_starts_with(const char *self, const char *prefix);
char *string_append(const char *left, const char *right);
