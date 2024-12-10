#include "index.h"

void
canvas_draw_glyph(
    canvas_t *self,
    size_t x, size_t y,
    const glyph_t *glyph,
    size_t scale,
    blending_t blending
) {
    size_t width = glyph_width(glyph);
    size_t height = glyph_height(glyph);

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            bool dot = glyph_get(glyph, i, j);
            color_t color = dot ? 3 : 0;
            for (size_t s = 0; s < scale; s++) {
                for (size_t t = 0; t < scale; t++) {
                    canvas_draw_color(
                        self,
                        x + i * scale + s,
                        y + j * scale + t,
                        color,
                        blending);
                }
            }
        }
    }
}
