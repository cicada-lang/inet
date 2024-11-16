#include "index.h"

char *
uint_to_string(unsigned int self) {
    char *buffer = allocate(100);
    sprintf(buffer, "%u", self);
    char *string = string_dup(buffer);
    free(buffer);
    return string;
}
