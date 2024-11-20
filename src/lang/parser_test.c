#include "index.h"

void
parser_test(void) {
    printf("<parser_test>\n");

    parser_t *parser = parser_new();
    parser->text = ""
        "* (zero) -- value!                   \n"
        "* (add1) prev -- value!              \n"
        "* (add) addend target! -- result     \n"
        "                                     \n"
        "! (zero)-(add)                       \n"
        "  (add)-addend result-(add)          \n"
        "                                     \n"
        "! (add1)-(add)                       \n"
        "  (add)-addend (add1)-prev add       \n"
        "  add1 result-(add)                  \n"
        "                                     \n"
        "= one zero add1                      \n"
        "= two one one add                    \n"
        "= three two one add                  \n"
        "= four two two add                   \n"
        "                                     \n"
        ". two two add two two add add        \n";

    parser_parse(parser);
    list_t *stmt_list = parser->stmt_list;
    parser_destroy(&parser);

    assert(list_length(stmt_list) == 10);

    printf("</parser_test>\n");
}
