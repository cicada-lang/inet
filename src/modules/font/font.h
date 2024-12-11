#pragma once

font_t *font_new(void);
void font_destroy(font_t **self_pointer);

glyph_t *font_get(const font_t *self, code_point_t code_point);
void font_put(font_t *self, glyph_t *glyph);

font_t *font_from_hex_string(const char *string);
font_t *font_from_hex_file(file_t *file);

glyph_t *font_first_glyph(font_t *self);
glyph_t *font_next_glyph(font_t *self, code_point_t code_point);

size_t font_text_width(const font_t *self, const text_t *text);
