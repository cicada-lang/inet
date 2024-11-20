#include "index.h"

file_t *
file_open_or_fail(
    const char *file_name,
    const char *mode,
    const char *message
) {
    file_t *file = fopen(file_name, mode);
    if (!file) {
        fprintf(stderr, "%s\n", message);
        fprintf(stderr, "[file_open_or_fail] file name: %s\n", file_name);
        fprintf(stderr, "[file_open_or_fail] mode: %s\n", mode);
        exit(1);
    }

    setbuf(file, NULL);
    return file;
}

static char *
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

off_t
file_size(file_t *file) {
    struct stat st;
    fstat(fileno(file), &st);
    return st.st_size;
}
