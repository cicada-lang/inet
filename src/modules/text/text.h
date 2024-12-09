#pragma once

text_t *text_new(size_t length);
void text_destroy(text_t **self_pointer);

text_t *text_from_string(const char *string);

size_t text_length(text_t *self);
code_point_t text_get(text_t *self, size_t index);
bool text_equal(text_t *left, text_t *right);
text_t *text_dup(text_t *self);
text_t *text_append(text_t *left, text_t *right);
text_t *text_slice(text_t *self, size_t start, size_t end);

char *text_to_string(text_t *self);
