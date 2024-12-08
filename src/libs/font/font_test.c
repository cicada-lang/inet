#include "index.h"

void
font_test(void) {
    glyph_test();

    printf("<font_test>\n");

    font_t *font = font_new();

    //

    font_destroy(&font);

    printf("</font_test>\n");
}
