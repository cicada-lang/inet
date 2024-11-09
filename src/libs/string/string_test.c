#include "index.h"

void
string_test(void) {
    printf("<string>");

    char *abc = string_clone("abc");
    char *_123 = string_clone("123");
    char *abc123 = string_append("abc", "123");

    assert(string_is_int(_123));
    assert(!string_is_int(abc123));

    string_destroy(&abc);
    assert(abc == NULL);

    printf("</string>\n");
}
