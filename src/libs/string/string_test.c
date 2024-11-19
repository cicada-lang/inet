#include "index.h"

void
string_test(void) {
    printf("<string>");

    assert(string_equal("abc", "abc"));
    assert(!string_equal("abc", "abd"));

    char *abc = string_dup("abc");
    assert(string_equal("abc", abc));

    string_destroy(&abc);
    assert(abc == NULL);

    assert(string_is_int("123"));
    assert(!string_is_int("a123"));

    char *abc123 = string_append("abc", "123");
    assert(string_equal(abc123, "abc123"));

    assert(string_starts_with(abc123, "abc"));
    assert(string_ends_with(abc123, "123"));

    assert(string_equal(string_slice("01234", 2, 4), "23"));

    assert(string_find_index("01234", '0') == 0);
    assert(string_find_index("01234", '1') == 1);
    assert(string_find_index("01234", '2') == 2);
    assert(string_find_index("01234", '5') == -1);

    assert(string_count_char("0aaa0", 'b') == 0);
    assert(string_count_char("0aaa0", 'a') == 3);
    assert(string_count_char("0aaa0", '0') == 2);

    printf("</string>\n");
}
