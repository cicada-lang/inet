#include "index.h"

void
modules_test(void) {
    printf("<modules_test>\n");

    char_test();
    string_test();
    list_test();
    dict_test();
    file_test();    
    array_test();
    stack_test();
    int_test();
    code_test();
    utf8_test();
    text_test();
    font_test();
    lexer_test();
    canvas_test();
    image_test();
    store_test();

    printf("</modules_test>\n");
}