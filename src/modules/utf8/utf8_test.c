#include "index.h"

void
utf8_test(void) {
    printf("<utf8_test>\n");

    assert(utf8_char_length('a') == 1);

    {
        const char *string = "中"; // 0xE4 0xB8 0xAD
        assert(utf8_char_length(string[0]) == 3);
    }

    {
        const char *string = "中";
        assert(utf8_decode(string) == 0x00004E2D);
    }

    {
        const char *string = "文";
        assert(utf8_decode(string) == 0x00006587);
    }

    {
        const char *string = "abc";
        assert(utf8_decode(string) == 0x61);
        assert(utf8_decode(string+1) == 0x62);
        assert(utf8_decode(string+2) == 0x63);
    }

    {
        const char *string = "abc 中文 123";
        utf8_iter_t *iter = utf8_iter_new(string);
        code_point_t code_point = utf8_iter_first(iter);
        size_t index = 0;
        while (code_point) {
            if (index == 0) assert(code_point == 0x61);
            if (index == 1) assert(code_point == 0x62);
            if (index == 2) assert(code_point == 0x63);
            if (index == 3) assert(code_point == 0x20);
            if (index == 4) assert(code_point == 0x4e2d);
            if (index == 5) assert(code_point == 0x6587);
            if (index == 6) assert(code_point == 0x20);
            if (index == 7) assert(code_point == 0x31);
            if (index == 8) assert(code_point == 0x32);
            if (index == 9) assert(code_point == 0x33);

            code_point = utf8_iter_next(iter);
            index++;
        }

        utf8_iter_destroy(&iter);
    }

    {
        const char *string = "";
        utf8_iter_t *iter = utf8_iter_new(string);
        code_point_t code_point = utf8_iter_first(iter);
        assert(code_point == 0);
        utf8_iter_destroy(&iter);
    }

    {
        assert(utf8_string_length("") == 0);
        assert(utf8_string_length("abc") == 3);
        assert(utf8_string_length("中文") == 2);
        assert(utf8_string_length("中") == 1);
        assert(utf8_string_length("abc 中文 123") == 10);
    }

    {
        assert(string_equal(utf8_encode(utf8_decode("a")), "a"));
        assert(string_equal(utf8_encode(utf8_decode("abc")), "a"));
        assert(string_equal(utf8_encode(utf8_decode("中")), "中"));
        assert(string_equal(utf8_encode(utf8_decode("中文")), "中"));
    }

    printf("</utf8_test>\n");
}
