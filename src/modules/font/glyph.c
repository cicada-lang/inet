#include "index.h"

// width and height are measured by pixel,
// currently only supported width is 8 and 16,
// only supported height is 16.

struct glyph_t {
    code_point_t code_point;
    size_t width;
    size_t height;
    uint8_t *bitmap;
};

glyph_t *
glyph_new(code_point_t code_point, size_t width, size_t height) {
    assert(code_point <= MAX_CODE_POINT);

    glyph_t *self = new(glyph_t);
    self->code_point = code_point;

    assert(width == 8 || width == 16);
    self->width = width;

    assert(height == 16);
    self->height = height;

    self->bitmap = allocate(height * width / 8);
    return self;
}

void
glyph_destroy(glyph_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        glyph_t *self = *self_pointer;
        free(self->bitmap);
        free(self);
        *self_pointer = NULL;
    }
}

code_point_t
glyph_code_point(const glyph_t *self) {
    return self->code_point;
}

size_t
glyph_width(const glyph_t *self) {
    return self->width;
}

size_t
glyph_height(const glyph_t *self) {
    return self->height;
}

bool
glyph_get(const glyph_t *self, size_t x, size_t y) {
    if (self->width == 8) {
        uint8_t byte = self->bitmap[y];
        return (byte << x) & 0x80;
    }

    assert(self->width == 16);
    if (x < 8) {
        uint8_t byte = self->bitmap[y * 2];
        return (byte << x) & 0x80;
    } else {
        uint8_t byte = self->bitmap[y * 2 + 1];
        return (byte << (x - 8)) & 0x80;
    }
}

void
glyph_set(const glyph_t *self, size_t x, size_t y, bool dot) {
    if (self->width == 8) {
        if (dot)
            self->bitmap[y] |= (uint8_t) 1 << x;
        else
            self->bitmap[y] &= ~((uint8_t) 1 << x);
        return;
    }

    assert(self->width == 16);
    if (x < 8) {
        if (dot)
            self->bitmap[y * 2] |= (uint8_t) 1 << x;
        else
            self->bitmap[y * 2] &= ~((uint8_t) 1 << x);
        return;
    } else {
        if (dot)
            self->bitmap[y * 2 + 1] |= (uint8_t) 1 << (x - 8);
        else
            self->bitmap[y * 2 + 1] &= ~((uint8_t) 1 << (x - 8));
        return;
    }
}

glyph_t *
glyph_decode_hex(const char* string) {
    int colon_index = string_find_index(string, ':');
    assert(colon_index != -1);

    code_point_t code_point = string_parse_uint(string, 16);
    string += colon_index + 1;

    int newline_index = string_find_index(string, '\n');
    if (newline_index == -1) {
        newline_index = string_find_index(string, '\0');
        assert(newline_index != -1);
    }

    size_t height = 16;
    // one hex char is 4 bits.
    size_t width = (newline_index * 4) / height;
    glyph_t *glyph = glyph_new(code_point, width, height);
    for (size_t i = 0; i < (size_t) newline_index; i += 2) {
        uint8_t high_nibble = char_to_hex(string[i]);
        uint8_t low_nibble = char_to_hex(string[i + 1]);
        uint8_t byte = (high_nibble << 4) + low_nibble;
        glyph->bitmap[i/2] = byte;
    }

    return glyph;
}

void
glyph_print_ascii_art(const glyph_t *self, char off_char, char on_char) {
    for (size_t y = 0; y < glyph_height(self); y++) {
        for (size_t x = 0; x < glyph_width(self); x++) {
            bool dot = glyph_get(self, x, y);
            if (dot) printf("%c%c", on_char, on_char);
            else printf("%c%c", off_char, off_char);;
        }

        printf("\n");
    }
}
