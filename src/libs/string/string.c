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
