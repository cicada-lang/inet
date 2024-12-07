#pragma once

typedef uint32_t code_point_t;

struct text_t {
    size_t length;
    code_point_t *code_points;
};

text_t *text_new(size_t length);
void text_destroy(text_t **self_pointer);
