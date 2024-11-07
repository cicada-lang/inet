#include "index.h"

typedef void *item_t;

struct stack_t {
    size_t size;
    size_t cursor;
    item_t *items;
};
