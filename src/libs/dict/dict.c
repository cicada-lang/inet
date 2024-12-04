#include "index.h"

struct entry_t {
    char *key;
    void *item;
};

struct dict_t {
    list_t *entry_list;
};
