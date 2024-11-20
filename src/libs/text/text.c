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
    // just count the number of '\n'.
    // the consting starts from 1.
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
    file_t* file,
    const char *text,
    size_t start,
    size_t end
) {
    size_t offset = 3;

    size_t start_lineno = text_lineno_of_index(text, start);
    size_t end_lineno = text_lineno_of_index(text, end);
    size_t max_lineno = end_lineno + offset;

    size_t left_padding = uint_decimal_string_length(max_lineno);
    size_t text_length = strlen(text);

    size_t current_lineno = 1;

    for (size_t i = 0; i < text_length; i++) {
        char c = text[i];
        // Do NOT use minus on unsigned int!
        if (start_lineno <= current_lineno + offset &&
            current_lineno <= end_lineno + offset) {
            if (i == 0 || text[i-1] == '\n') {
                if (start_lineno <= current_lineno &&
                    current_lineno <= end_lineno) {
                    fprintf(file, "> %*lu|", (int) left_padding, current_lineno);
                } else {
                    fprintf(file, "  %*lu|", (int) left_padding, current_lineno);
                }
            }

            fprintf(file, "%c", c);
        }

        if (c == '\n') current_lineno++;
    }
}
