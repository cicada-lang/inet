#include "index.h"

void
image_test(void) {
    printf("<image_test>\n");

    assert(image_hex_width_from_path("button10x10.chr") == 0x10);
    assert(image_hex_height_from_path("button10x10.chr") == 0x10);

    printf("</image_test>\n");
}
