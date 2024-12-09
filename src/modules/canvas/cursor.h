#pragma once

struct cursor_t {
    size_t x, y;
};

cursor_t *cursor_new(size_t x, size_t y);
void cursor_destroy(cursor_t **self_pointer);
