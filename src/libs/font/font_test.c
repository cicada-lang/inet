#include "index.h"

void
font_test(void) {
    glyph_test();

    printf("<font_test>\n");

    {
        font_t *font = font_new();
        font_destroy(&font);
    }

    char *base = dirname(string_dup(__FILE__));
    char *file_name = string_append(base, "/unifont-ascii.hex");
    file_t *file = file_open_or_fail(file_name, "r");
    font_t *font = font_from_hex_file(file);

    for (code_point_t i = 0; i < 0x80; i++) {
        glyph_t *glyph = font_get(font, i);

        if (glyph) {
            printf("ascii code point: ox%x\n", i);
            printf("\n");
            glyph_print_ascii_art(glyph, ' ', '#');
            printf("\n");
        } else {
            printf("no font for ascii code point: ox%x\n", i);
        }
    }

    font_destroy(&font);

    printf("</font_test>\n");
}
