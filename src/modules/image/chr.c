#include "index.h"

uint8_t *
chr_subimage(
    uint8_t *bytes, size_t width,
    size_t start_col, size_t start_row,
    size_t subwidth, size_t subheight
) {
    assert(TILE == 8);

    // one tile in chr has TILE * 2 bytes.
    uint8_t *subimage = allocate(subwidth * subheight * TILE * 2);

    for (size_t row = 0; row < subheight; row++) {
        for (size_t col = 0; col < subwidth; col++) {
            for (size_t line = 0; line < TILE; line++) {
                size_t index =
                    (start_row + row) * TILE * 2 * width +
                    (start_col + col) * TILE * 2 +
                    line;
                size_t subindex =
                    row * TILE * 2 * subwidth +
                    col * TILE * 2 +
                    line;
                subimage[subindex] = bytes[index];
                subimage[subindex + TILE] = bytes[index + TILE];
            }
        }
    }

    return subimage;
}
