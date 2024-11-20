#include "index.h"

void
parser_test(void) {
    printf("<parser_test>\n");

    const char *text = "\
* (zero) -- value!                   \
* (add1) prev -- value!              \
* (add) addend target! -- result     \
                                     \
! (zero)-(add)                       \
  (add)-addend result-(add)          \
                                     \
! (add1)-(add)                       \
  (add)-addend (add1)-prev add       \
  add1 result-(add)                  \
                                     \
= one zero add1                      \
= two one one add                    \
= three two one add                  \
= four two two add                   \
                                     \
. two two add two two add            \
";

    parser_t *parser = parser_new("parser_test", text);
    parser_parse(parser);
    list_t *stmt_list = parser->stmt_list;
    parser_destroy(&parser);


    assert(list_length(stmt_list) == 10);

    printf("</parser_test>\n");
}
