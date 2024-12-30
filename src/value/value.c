#include "index.h"

tag_t
value_tag(value_t value) {
    return (size_t) value & TAG_MASK;
}

void
value_print(value_t value, file_t *file) {
    if (value == xnull) {
        fprintf(file, "null");
        return;
    }

    if (value == xtrue) {
        fprintf(file, "true");
        return;
    }

    if (value == xfalse) {
        fprintf(file, "false");
        return;
    }

    if (is_xint(value)) {
        fprintf(file, "%ld", to_int64(value));
        return;
    }

    if (is_xfloat(value)) {
        char buffer[64];
        sprintf(buffer, "%.17g", to_double(value));
        if (!string_has_char(buffer, '.')) {
            size_t end = string_length(buffer);
            buffer[end] = '.';
            buffer[end + 1] = '0';
            buffer[end + 2] = '\0';
        }

        fprintf(stdout, "%s", buffer);
        return;
    }

    fprintf(file, "<0x%lx>", (uint64_t) value);
    return;
}
