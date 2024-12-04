#include "index.h"

uint8_t
image_width_from_path(const char *path) {
    size_t length = strlen(path);
    const char *width_start = path + (length - 9);
    return strtol(width_start, NULL, 16);
}

uint8_t
image_height_from_path(const char *path) {
    size_t length = strlen(path);
    const char *height_start = path + (length - 6);
    return strtol(height_start, NULL, 16);
}
