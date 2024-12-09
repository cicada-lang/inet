#include "index.h"

void
canvas_draw_text(
    canvas_t *self,
    size_t x, size_t y,
    const text_t *text,
    size_t scale,
    blending_t blending
) {
    assert(self->font);

    size_t width = 0;
    for (size_t i = 0; i < text_length(text); i++) {
        code_point_t code_point = text_get(text, i);
        glyph_t *glyph = font_get(self->font, code_point);
        canvas_draw_glyph(self, x + width, y, glyph, scale, blending);
        width += glyph_width(glyph) * scale;
    }
}
