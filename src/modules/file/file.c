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

char *
file_read_string(file_t *file) {
    off_t size = file_size(file);
    char *string = allocate(size + 1); // +1 for the ending '\0'.
    size_t nbytes = fread(string, 1, size, file);
    assert(nbytes == (size_t) size);
    return string;
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

blob_t *
file_read_blob(file_t *file) {
    off_t size = file_size(file);
    blob_t *blob = blob_new(size);
    uint8_t *bytes = blob_bytes(blob);
    size_t nbytes = fread(bytes, 1, size, file);
    assert(nbytes == (size_t) size);
    return blob;
}

void
file_write_blob(file_t *file, blob_t *blob) {
    fwrite(blob_bytes(blob), 1, blob_size(blob), file);
}
