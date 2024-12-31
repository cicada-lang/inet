#include "index.h"

void
set_test(void) {
    printf("<set_test>\n");

    set_t *set = set_new();
    assert(set_length(set) == 0);

    //

    set_destroy(&set);

    printf("</set_test>\n");
}
