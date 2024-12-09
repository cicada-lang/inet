#pragma once

// col, row, width, height are all measured in tile.
uint8_t *chr_subimage(
    uint8_t *bytes, size_t width,
    size_t start_col, size_t start_row,
    size_t subwidth, size_t subheight);
