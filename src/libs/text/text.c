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
