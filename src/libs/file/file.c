#include "index.h"

bool
file_exists(const char *file_name) {
    return access(file_name, F_OK) != -1;
}

file_t *
file_open_or_fail(
    const char *file_name,
    const char *mode
) {
    file_t *file = fopen(file_name, mode);
    if (!file) {
        fprintf(stderr, "[file_open_or_fail] file name: %s\n", file_name);
        fprintf(stderr, "[file_open_or_fail] mode: %s\n", mode);
        exit(1);
    }

    setbuf(file, NULL);
    return file;
}

off_t
file_size(file_t *file) {
    struct stat st;
    fstat(fileno(file), &st);
    return st.st_size;
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
file_read_string(file_t *file) {
    char *string = string_empty();
    while (true) {
        char *line = file_readline(file);
        if (!line) return string;

        char *new_string = string_append(string, line);
        free(string);
        free(line);
        string = new_string;
    }
}

uint8_t *
file_read_bytes(file_t *file) {
    off_t size = file_size(file);
    uint8_t *bytes = allocate(size);
    size_t nbytes = fread(bytes, 1, size, file);
    assert(nbytes == (size_t) size);
    return bytes;
}

void
file_write_bytes(file_t *file, uint8_t *bytes, size_t size) {
    fwrite(bytes, 1, size, file);
}
