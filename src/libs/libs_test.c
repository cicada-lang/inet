#include "index.h"

void
libs_test(void) {
    printf("<libs_test>\n");

    string_test();
    list_test();
    dict_test();
    array_test();
    stack_test();
    int_test();
    code_test();
    text_test();
    lexer_test();
    canvas_test();
    image_test();
    store_test();

    printf("</libs_test>\n");
}
