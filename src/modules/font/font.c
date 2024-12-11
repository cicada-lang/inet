#include "index.h"

struct font_t {
    glyph_t **glyphs;
};

font_t *
font_new(void) {
    font_t *self = new(font_t);
    // length is one more than the max.
    self->glyphs = allocate_pointers(MAX_CODE_POINT + 1);
    return self;
}

void
font_destroy(font_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        font_t *self = *self_pointer;
        free(self->glyphs);
        free(self);
        *self_pointer = NULL;
    }
}

glyph_t *
font_get(const font_t *self, code_point_t code_point) {
    assert(code_point <= MAX_CODE_POINT);
    return self->glyphs[code_point];
}

void
font_put(font_t *self, glyph_t *glyph) {
    self->glyphs[glyph_code_point(glyph)] = glyph;
}

font_t *
font_from_hex_string(const char *string) {
    font_t *font = font_new();
    const char *line = string;
    while (line) {
        font_put(font, glyph_decode_hex(line));
        line = string_next_line(line);
    }

    return font;
}

font_t *
font_from_hex_file(file_t *file) {
    char *string = file_read_string(file);
    font_t *font = font_from_hex_string(string);
    free(string);
    return font;
}

glyph_t *
font_first_glyph(font_t *self) {
    code_point_t code_point = 0;
    while (code_point <= MAX_CODE_POINT) {
        glyph_t *glyph = font_get(self, code_point);
        if (glyph) return glyph;
        code_point++;
    }

    return NULL;
}

glyph_t *
font_next_glyph(font_t *self, code_point_t code_point) {
    code_point++;
    while (code_point <= MAX_CODE_POINT) {
        glyph_t *glyph = font_get(self, code_point);
        if (glyph) return glyph;
        code_point++;
    }

    return NULL;
}

size_t
font_text_width(const font_t *self, const text_t *text) {
    size_t width = 0;

    for (size_t i = 0; i < text_length(text); i++) {
        code_point_t code_point = text_get(text, i);
        glyph_t *glyph = font_get(self, code_point);
        if (glyph) {
            width += glyph_width(glyph);
        } else {
            width += 16;
        }
    }

    return width;
}
