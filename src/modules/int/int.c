#include "index.h"

uint64_t
uint_max(uint64_t x, uint64_t y) {
    if (x > y) return x;
    else return y;
}

uint64_t
uint_min(uint64_t x, uint64_t y) {
    if (x < y) return x;
    else return y;
}

#define MAX_STRING_LENGTH 256

char *
uint_to_string(uint64_t self) {
    char *buffer = allocate(MAX_STRING_LENGTH);
    sprintf(buffer, "%lu", self);
    char *string = string_copy(buffer);
    free(buffer);
    return string;
}

// ₀₁₂₃₄₅₆₇₈₉₊₋₌₍₎

char *
uint_to_subscript(uint64_t self) {
    char *buffer = allocate(MAX_STRING_LENGTH);
    char *number_string = uint_to_string(self);
    for (size_t i = 0; i < strlen(number_string); i++) {
        char ch = number_string[i];
        switch (ch) {
        case '0': { strcat(buffer, "₀"); break; }
        case '1': { strcat(buffer, "₁"); break; }
        case '2': { strcat(buffer, "₂"); break; }
        case '3': { strcat(buffer, "₃"); break; }
        case '4': { strcat(buffer, "₄"); break; }
        case '5': { strcat(buffer, "₅"); break; }
        case '6': { strcat(buffer, "₆"); break; }
        case '7': { strcat(buffer, "₇"); break; }
        case '8': { strcat(buffer, "₈"); break; }
        case '9': { strcat(buffer, "₉"); break; }
        }

    }

    char *subscript_string = string_copy(buffer);
    free(buffer);
    return subscript_string;
}


// ⁰¹²³⁴⁵⁶⁷⁸⁹⁺⁻⁼⁽⁾

char *
uint_to_superscript(uint64_t self) {
    char *buffer = allocate(MAX_STRING_LENGTH);
    char *number_string = uint_to_string(self);
    for (size_t i = 0; i < strlen(number_string); i++) {
        char ch = number_string[i];
        switch (ch) {
        case '0': { strcat(buffer, "⁰"); break; }
        case '1': { strcat(buffer, "¹"); break; }
        case '2': { strcat(buffer, "²"); break; }
        case '3': { strcat(buffer, "³"); break; }
        case '4': { strcat(buffer, "⁴"); break; }
        case '5': { strcat(buffer, "⁵"); break; }
        case '6': { strcat(buffer, "⁶"); break; }
        case '7': { strcat(buffer, "⁷"); break; }
        case '8': { strcat(buffer, "⁸"); break; }
        case '9': { strcat(buffer, "⁹"); break; }
        }
    }

    char *superscript_string = string_copy(buffer);
    free(buffer);
    return superscript_string;
}

size_t
uint_decimal_length(uint64_t self) {
    char *decimal_string = uint_to_string(self);
    size_t length = strlen(decimal_string);
    free(decimal_string);
    return length;
}

uint64_t
int_relu(int64_t self) {
    if (self > 0) {
        return self;
    } {
        return 0;
    }
}
