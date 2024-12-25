#include "index.h"

void
string_test(void) {
    printf("<string_test>\n");

    assert(string_equal("abc", "abc"));
    assert(!string_equal("abc", "abd"));

    char *abc = string_copy("abc");
    assert(string_equal("abc", abc));

    assert(string_length("") == 0);
    assert(string_length("1") == 1);
    assert(string_length("12") == 2);
    assert(string_length("123") == 3);

    string_destroy(&abc);
    assert(abc == NULL);

    {
        assert(string_is_int_of_base("123", 10));
        assert(string_is_int_of_base("-123", 10));

        assert(!string_is_int_of_base("123", 3));
        assert(!string_is_int_of_base("-123", 3));
    }

    {
        assert(string_is_int("123"));
        assert(string_is_int("-123"));
        assert(string_is_int("+123"));
        assert(!string_is_int("a123"));
        assert(!string_is_int("123a"));

        assert(!string_is_int("0x123z"));
        assert(string_is_int("0x123a"));
        assert(string_is_int("0x123A"));
        assert(string_is_int("-0x123a"));
        assert(!string_is_int("--0x123A"));

        // 0b is handled by c32.
        assert(string_is_int("0b10"));
        // 0o is not handled by c.
        assert(!string_is_int("0o10"));
    }

    {
        assert(string_parse_int("", 10) == 0);
        assert(string_parse_int("-", 10) == 0);
        assert(string_parse_int("-1", 10) == -1);
        assert(string_parse_int("123", 10) == 123);
        assert(string_parse_int("+123", 10) == 123);
        assert(string_parse_int("-123", 10) == -123);

        assert(string_parse_int("0x10", 16) == 16);
        assert(string_parse_int("+0x10", 16) == 16);
        assert(string_parse_int("-0x10", 16) == -16);

        assert(string_parse_int("010", 8) == 8);
        assert(string_parse_int("-010", 8) == -8);

        assert(string_parse_int("10", 8) == 8);
        assert(string_parse_int("-10", 8) == -8);

        assert(string_parse_int("10", 2) == 2);
        assert(string_parse_int("-10", 2) == -2);
    }

    {
        assert(string_parse_uint("", 16) == 0);
        assert(string_parse_uint("f", 16) == 15);
        assert(string_parse_uint("F", 16) == 15);
        assert(string_parse_uint("ff", 16) == 255);
        assert(string_parse_uint("FF", 16) == 255);
        assert(string_parse_uint("FF:123", 16) == 255);
    }

    char *abc123 = string_append("abc", "123");
    assert(string_equal(abc123, "abc123"));

    assert(string_starts_with(abc123, "abc"));
    assert(string_ends_with(abc123, "123"));

    assert(string_equal(string_slice("01234", 2, 4), "23"));

    assert(string_find_index("01234", '0') == 0);
    assert(string_find_index("01234", '1') == 1);
    assert(string_find_index("01234", '2') == 2);
    assert(string_find_index("01234", '5') == -1);
    assert(string_find_index("", '5') == -1);
    assert(string_find_index("", '\0') == 0);

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



    {
        assert(string_next_line("") == NULL);
        assert(string_next_line("abc") == NULL);
        assert(string_next_line("abc\n") == NULL);
    }

    {
        const char *string =
            "123\n"
            "456\n"
            "789\n";

        const char *line = string;
        size_t count = 0;
        while (line) {
            if (count == 0) assert(string_starts_with(line, "123\n"));
            if (count == 1) assert(string_starts_with(line, "456\n"));
            if (count == 2) assert(string_starts_with(line, "789\n"));
            if (count == 3) assert(line == NULL);

            line = string_next_line(line);
            count++;
        }
    }

    {
        // no ending newline.

        const char *string =
            "123\n"
            "456\n"
            "789";

        const char *line = string;
        size_t count = 0;
        while (line) {
            if (count == 0) assert(string_starts_with(line, "123\n"));
            if (count == 1) assert(string_starts_with(line, "456\n"));
            if (count == 2) assert(string_starts_with(line, "789"));
            if (count == 3) assert(line == NULL);

            line = string_next_line(line);
            count++;
        }
    }

    {
        assert(string_is_xint("0b10"));
        assert(string_is_xint("+0b10"));
        assert(string_is_xint("-0b10"));
        assert(!string_is_xint("0b12"));
        assert(!string_is_xint("++0b10"));
        assert(!string_is_xint("--0b11"));
    }

    {
        assert(string_parse_xint("0b10") == 2);
        assert(string_parse_xint("+0b10") == 2);
        assert(string_parse_xint("-0b10") == -2);

        assert(string_parse_xint("0o10") == 8);
        assert(string_parse_xint("+0o10") == 8);
        assert(string_parse_xint("-0o10") == -8);

        assert(string_parse_xint("0x10") == 16);
        assert(string_parse_xint("+0x10") == 16);
        assert(string_parse_xint("-0x10") == -16);

        assert(string_parse_xint("10") == 10);
        assert(string_parse_xint("+10") == 10);
        assert(string_parse_xint("-10") == -10);
    }

    {
        assert(string_is_double("0"));
        assert(string_is_double("0.1"));
        assert(string_is_double(".1"));
        assert(string_is_double("0.0"));

        assert(string_is_double("+0"));
        assert(string_is_double("+0.1"));
        assert(string_is_double("+.1"));
        assert(string_is_double("+0.0"));

        assert(string_is_double("-0"));
        assert(string_is_double("-0.1"));
        assert(string_is_double("-.1"));
        assert(string_is_double("-0.0"));
    }

    {
        assert(string_parse_double("0") == 0);
        assert(string_parse_double("0.1") == 0.1);
        assert(string_parse_double(".1") == 0.1);
        assert(string_parse_double("0.0") == 0);

        assert(string_parse_double("+0") == 0);
        assert(string_parse_double("+0.1") == 0.1);
        assert(string_parse_double("+.1") == 0.1);
        assert(string_parse_double("+0.0") == 0);

        assert(string_parse_double("-0") == 0);
        assert(string_parse_double("-0.1") == -0.1);
        assert(string_parse_double("-.1") == -0.1);
        assert(string_parse_double("-0.0") == 0);
    }

    printf("</string_test>\n");
}
