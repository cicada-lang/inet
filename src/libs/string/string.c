#include "index.h"

void
string_destroy(char **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        char *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

char*
string_dup(const char *self) {
    size_t length = strlen(self);
    char *string = malloc(length + 1);
    assert(string);
    strcpy(string, self);
    return string;
}

char *
string_empty(void) {
    char *s = malloc(1);
    s[0] = '\0';
    return s;
}

bool
string_equal(const char *left, const char *right) {
    return strcmp(left, right) == 0;
}

size_t
string_hash(const char *self, size_t size) {
    size_t max_index = 64 - 8;
    size_t index = 0;
    size_t hash = 0;
    while (*self) {
        hash += (*self) << (index % max_index);
        if (hash > size) hash %= size;
        index++;
        self++;
    }

    return hash;
}

bool
string_is_int(const char *self) {
    char *int_end = NULL;
    strtol(self, &int_end, 0);
    if (int_end == self) return false;
    return *int_end == '\0';
}

int64_t
string_to_int(const char *self) {
    char *int_end = NULL;
    return strtol(self, &int_end, 0);
}

bool
string_starts_with(const char *target, const char *prefix) {
    size_t target_length = strlen(target);
    size_t prefix_length = strlen(prefix);

    if (target_length < prefix_length) return false;

    return strncmp(target, prefix, prefix_length) == 0;
}

bool
string_ends_with(const char *target, const char *postfix) {
    size_t target_length = strlen(target);
    size_t postfix_length = strlen(postfix);

    if (target_length < postfix_length) return false;

    return strncmp(target + (target_length - postfix_length),
                   postfix,
                   postfix_length) == 0;
}

char *
string_append(const char *left, const char *right) {
    assert(left);
    assert(right);
    size_t left_length = strlen(left);
    size_t right_length = strlen(right);
    char *result = malloc(left_length + right_length + 1);
    result[0] = '\0';
    strcat(result, left);
    strcat(result, right);
    return result;
}

char *
string_slice(const char *self, size_t start, size_t end) {
    size_t length = end - start;
    char *result = malloc(length + 1);
    memcpy(result, self + start, length);
    result[length] = '\0';
    return result;
}

int
string_find_index(const char *self, char ch) {
    char *p = strchr(self, ch);
    if (!p) return -1;
    else return (int)(p - self);
}

size_t
string_count_char(const char *self, char ch) {
    size_t count = 0;
    size_t length = strlen(self);
    for (size_t i = 0; i < length; i++) {
        if (self[i] == ch) count++;
    }

    return count;
}

bool string_has_char(const char *self, char ch) {
    return string_count_char(self, ch) > 0;
}

size_t
string_count_substring(const char *self, const char* substring) {
    size_t count = 0;
    size_t length = strlen(self);
    for (size_t i = 0; i < length; i++) {
        if (string_starts_with(self+i, substring)) count++;
    }

    return count;
}
