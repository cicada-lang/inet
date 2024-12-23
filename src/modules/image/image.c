#include "index.h"

uint8_t
image_hex_width_from_path(const char *path) {
    size_t length = string_length(path);
    char *width_string = string_slice(path, length - 9, length);
    uint8_t width = string_parse_uint(width_string, 16);
    free(width_string);
    return width;
}

uint8_t
image_hex_height_from_path(const char *path) {
    size_t length = string_length(path);
    char *height_string = string_slice(path, length - 6, length);
    uint8_t height = string_parse_uint(height_string, 16);
    free(height_string);
    return height;
}
