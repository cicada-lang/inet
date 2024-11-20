#include "index.h"

char *
file_readline(file_t *file) {
    size_t line_max_length  = 1000 * 1000;
    char *buffer = allocate(line_max_length);

    char *ok = fgets(buffer, line_max_length, file);
    if (ok) {
        char *line = string_dup(buffer);
        free(buffer);
        return line;
    } else {
        free(buffer);
        return NULL;
    }
}

char *
file_read(file_t *file) {
    char *text = string_empty();
    while (true) {
        char *line = file_readline(file);
        if (!line) return text;

        char *new_text = string_append(text, line);
        free(text);
        free(line);
        text = new_text;
    }
}
