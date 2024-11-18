#include "index.h"

size_t
text_max_lineno(const char *text) {
    size_t lineno = 1;
    size_t text_length = strlen(text);
    for (size_t i = 0; i < text_length; i++) {
        if (text[i] == '\n') lineno++;
    }

    return lineno;
}

size_t
text_lineno_of_index(const char *text, size_t index) {
    // just count the number of '\n'
    // starting from 1
    size_t lineno = 1;
    size_t text_length = strlen(text);
    for (size_t i = 0; i < text_length; i++) {
        if (i >= index) break;
        else if (text[i] == '\n') lineno++;
    }

    return lineno;
}

void
text_print_context(
    const char *text,
    size_t start,
    size_t end
) {
    size_t offset = 3;
    size_t max_lineno = text_max_lineno(text);

    size_t start_lineno =
        uint_max(text_lineno_of_index(text, start) - offset,
                 1);
    size_t end_lineno =
        uint_min(text_lineno_of_index(text, end) + offset,
                 max_lineno);

    size_t text_length = strlen(text);
    size_t current_lineno = 1;
    for (size_t i = 0; i < text_length; i++) {
        char c = text[i];
        if (c == '\n') current_lineno++;
        if (start_lineno <= current_lineno && current_lineno <= end_lineno) {
            printf("%c", c);
        }
    }

    printf("\n");
}
