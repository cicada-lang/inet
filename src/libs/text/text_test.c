#include "index.h"

void
text_test(void) {
    printf("<text_test>\n");

    {
        const char *text = ""
            ".\n"
            "12345\n"
            ".";

        assert(text_max_lineno(text) == 3);
    }

    {
        const char *text = ""
            ".\n"
            "12345\n"
            ".\n";

        assert(text_max_lineno(text) == 4);
    }

    {
        const char *text = ""
            ".\n"
            "12345\n"
            ".\n";

        assert(text_lineno_of_index(text, 0) == 1);
        assert(text_lineno_of_index(text, 1) == 1);
        assert(text_lineno_of_index(text, 100) == 4);
    }

    printf("</text_test>\n");
}
