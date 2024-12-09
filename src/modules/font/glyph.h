#pragma once

#define MAX_CODE_POINT 0x10FFFF

glyph_t *glyph_new(code_point_t code_point, size_t width, size_t height);
void glyph_destroy(glyph_t **self_pointer);

code_point_t glyph_code_point(const glyph_t *self);
size_t glyph_width(const glyph_t *self);
size_t glyph_height(const glyph_t *self);

bool glyph_get(const glyph_t *self, size_t x, size_t y);
void glyph_set(const glyph_t *self, size_t x, size_t y, bool dot);

glyph_t *glyph_decode_hex(const char* string);
void glyph_print_ascii_art(const glyph_t *self, char off_char, char on_char);
