#include "index.h"

void
hash_test(void) {
    printf("<hash_test>\n");

    {
        uintptr_t key = (uintptr_t) string_dup("123");
        printf("key: %lu\n", key);
    }

    {
        void *key = string_dup("123");
        printf("key: %p\n", key);
    }

    //

    printf("</hash_test>\n");
}
