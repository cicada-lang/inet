#include "index.h"

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
    // size_t offset = 3;
    size_t start_lineno = text_lineno_of_index(text, start);
    size_t end_lineno = text_lineno_of_index(text, end);
    size_t current_lineno = 1;
    size_t text_length = strlen(text);
    for (size_t i = 0; i < text_length; i++) {
        char c = text[i];
        if (c == '\n') current_lineno++;
        if (start_lineno <= current_lineno && current_lineno <= end_lineno) {
            printf("%c", c);
        }
    }
}
