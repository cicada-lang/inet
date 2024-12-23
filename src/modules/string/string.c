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
string_copy(const char *self) {
    size_t length = strlen(self);
    char *string = malloc(length + 1);
    assert(string);
    strcpy(string, self);
    return string;
}

size_t
string_length(const char *self) {
    return strlen(self);
}

char *
string_empty(void) {
    char *s = malloc(1);
    s[0] = '\0';
    return s;
}

bool
string_equal(const char *left, const char *right) {
    if (left == right) return true;

    return strcmp(left, right) == 0;
}

size_t
string_bernstein_hash(const char *self) {
    const char *pointer = (const char *) self;
    size_t hash = 0;
    while (*pointer)
        hash = 33 * hash ^ *pointer++;
    return hash;
}

bool
string_is_int_of_base(const char *self, size_t base) {
    char *end = NULL;
    strtol(self, &end, base);
    if (end == self) return false;
    return *end == '\0';
}

bool
string_is_int(const char *self) {
    char *end = NULL;
    strtol(self, &end, 0);
    if (end == self) return false;
    return *end == '\0';
}

int64_t
string_parse_int(const char *self, size_t base) {
    char *end = NULL;
    return strtol(self, &end, base);
}

uint64_t
string_parse_uint(const char *self, size_t base) {
    char *end = NULL;
    return strtoul(self, &end, base);
}

bool
string_is_double(const char *self) {
    char *end = NULL;
    strtod(self, &end);
    if (end == self) return false;
    return *end == '\0';
}

double
string_parse_double(const char *self) {
    char *end = NULL;
    return strtod(self, &end);
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
    assert(end >= start);
    assert(end <= string_length(self));
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

char *
string_to_lower_case(const char *self) {
    char *result = string_copy(self);
    for (size_t i = 0; i < string_length(result); i++) {
        result[i] = tolower((unsigned char) result[i]);
    }

    return result;
}

char *
string_to_upper_case(const char *self) {
    char *result = string_copy(self);
    for (size_t i = 0; i < string_length(result); i++) {
        result[i] = toupper((unsigned char) result[i]);
    }

    return result;
}

bool
string_equal_mod_case(const char *left, const char *right) {
    char *left_upper = string_to_upper_case(left);
    char *right_upper = string_to_upper_case(right);

    bool result = string_equal(left_upper, right_upper);

    free(left_upper);
    free(right_upper);

    return result;
}

const char *
string_next_line(const char *self) {
    int newline_index = string_find_index(self, '\n');
    if (newline_index == -1) {
        return NULL;
    }

    const char *next_line = self + newline_index + 1;
    if (*next_line == '\0')
        return NULL;

    return next_line;
}

bool
string_is_xint(const char *self) {
    size_t length = string_length(self);

    if (string_starts_with(self, "-") ||
        string_starts_with(self, "+"))
    {

        char *substring = string_slice(self, 1, length);
        if (string_starts_with(substring, "-") ||
            string_starts_with(substring, "+"))
        {
            free(substring);
            return false;
        }

        bool result = string_is_xint(substring);
        free(substring);
        return result;
    }

    if (string_starts_with(self, "0x")) {
        char *substring = string_slice(self, 2, length);
        bool result = string_is_int_of_base(substring, 16);
        free(substring);
        return result;
    }

    if (string_starts_with(self, "0o")) {
        char *substring = string_slice(self, 2, length);
        bool result = string_is_int_of_base(substring, 8);
        free(substring);
        return result;
    }

    if (string_starts_with(self, "0b")) {
        char *substring = string_slice(self, 2, length);
        bool result = string_is_int_of_base(substring, 2);
        free(substring);
        return result;
    }

    return string_is_int_of_base(self, 10);
}

int64_t
string_parse_xint(const char *self) {
    size_t length = string_length(self);

    if (string_starts_with(self, "-")) {
        char *substring = string_slice(self, 1, length);
        int64_t result = string_parse_xint(substring);
        free(substring);
        return -result;
    }

    if (string_starts_with(self, "+")) {
        char *substring = string_slice(self, 1, length);
        int64_t result = string_parse_xint(substring);
        free(substring);
        return result;
    }

    if (string_starts_with(self, "0x")) {
        char *substring = string_slice(self, 2, length);
        int64_t result = string_parse_int(substring, 16);
        free(substring);
        return result;
    }

    if (string_starts_with(self, "0o")) {
        char *substring = string_slice(self, 2, length);
        int64_t result = string_parse_int(substring, 8);
        free(substring);
        return result;
    }

    if (string_starts_with(self, "0b")) {
        char *substring = string_slice(self, 2, length);
        int64_t result = string_parse_int(substring, 2);
        free(substring);
        return result;
    }

    return string_parse_int(self, 10);
}
