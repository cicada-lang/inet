#pragma once

void string_destroy(char **self_pointer);
char *string_dup(const char *self);
size_t string_length(const char *self);
char *string_empty(void);
bool string_equal(const char *left, const char *right);
size_t string_bernstein_hash(const char *self);
bool string_is_int(const char *restrict self);
int64_t string_parse_int(const char *self);
uint64_t string_parse_hex(const char *self);
bool string_starts_with(const char *self, const char *prefix);
bool string_ends_with(const char *self, const char *postfix);
char *string_append(const char *left, const char *right);
char *string_slice(const char *self, size_t start, size_t end);
int string_find_index(const char *self, char ch);
size_t string_count_char(const char *self, char ch);
bool string_has_char(const char *self, char ch);
size_t string_count_substring(const char *self, const char* substring);
char *string_to_lower_case(const char *self);
char *string_to_upper_case(const char *self);
bool string_equal_mod_case(const char *left, const char *right);
const char *string_next_line(const char *self);
