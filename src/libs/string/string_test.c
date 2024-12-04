#include "index.h"

void
string_test(void) {
    printf("<string>");

    assert(string_equal("abc", "abc"));
    assert(!string_equal("abc", "abd"));

    char *abc = string_dup("abc");
    assert(string_equal("abc", abc));

    assert(string_length("") == 0);
    assert(string_length("1") == 1);
    assert(string_length("12") == 2);
    assert(string_length("123") == 3);

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

    assert(!string_has_char("0aaa0", 'b'));
    assert(string_has_char("0aaa0", 'a'));
    assert(string_has_char("0aaa0", '0'));

    assert(string_count_substring("0aaa0", "a") == 3);
    assert(string_count_substring("0aaa0", "aa") == 2);
    assert(string_count_substring("0aaa0", "aaa") == 1);
    assert(string_count_substring("0aaa0aaa", "aa") == 4);
    assert(string_count_substring("0aaa0aaa", "aaa") == 2);

    assert(string_equal(string_to_lower_case("ABC"), "abc"));
    assert(string_equal(string_to_upper_case("abc"), "ABC"));

    assert(string_equal_mod_case("ABC", "abc"));
    assert(string_equal_mod_case("abc", "ABC"));

    printf("</string>\n");
}
