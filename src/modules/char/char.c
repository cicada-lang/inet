#include "index.h"

// https://en.wikipedia.org/wiki/ASCII

uint8_t
char_to_hex(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    if ('A' <= c && c <= 'F') return c - 'A' + 10;

    fprintf(stderr, "[char_to_hex] unknown char: %c\n", c);
    exit(1);
}

bool
char_is_digit(char c) {
    return ('0' <= c && c <= '9');
}
