#include "index.h"

void
int_test(void) {
    printf("<int_test>\n");

    assert(string_equal(uint_to_string(123), "123"));
    assert(string_equal(uint_to_subscript(123), "₁₂₃"));
    // assert(string_equal(uint_to_superscript(123), "¹²³"));

    printf("</int_test>\n");
}
