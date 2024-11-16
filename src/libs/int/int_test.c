#include "index.h"

void
int_test(void) {
    printf("<int_test>\n");

    assert(string_equal(uint_to_string(123), "123"));

    printf("</int_test>\n");
}
