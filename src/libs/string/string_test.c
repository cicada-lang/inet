#include "index.h"

void
string_test(void) {
    printf("<string>");

    assert(string_equal("abc", "abc"));
    assert(!string_equal("abc", "abd"));

    char *abc = string_clone("abc");
    assert(string_equal("abc", abc));

    string_destroy(&abc);
    assert(abc == NULL);

    assert(string_is_int("123"));
    assert(!string_is_int("a123"));

    char *abc123 = string_append("abc", "123");
    assert(string_equal(abc123, "abc123"));

    assert(string_starts_with(abc123, "abc"));

    printf("</string>\n");
}
