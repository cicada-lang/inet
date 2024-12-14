#pragma once

struct utf8_iter_t {
    size_t cursor;
    const char *string;
};

utf8_iter_t *utf8_iter_new(const char *string);
void utf8_iter_destroy(utf8_iter_t **self_pointer);

// We view code point 0 as the ending point like in c string.
code_point_t utf8_iter_current(utf8_iter_t *self);
code_point_t utf8_iter_first(utf8_iter_t *self);
code_point_t utf8_iter_next(utf8_iter_t *self);
