#pragma once

char *string_clone(const char *s);
char *string_empty(void);
bool string_equal(const char *left, const char *right);
size_t string_hash(const char *s, size_t size);
bool string_is_int(const char *restrict s);
int64_t string_to_int(const char *s);
bool string_starts_with(const char *target, const char *prefix);
char *string_append(const char *left, const char *right);
