#include "index.h"

void
parser_test(void) {
    printf("<parser_test>\n");

    list_t *stmt_list = parse("\
* (zero) -- value!                   \
* (add1) prev -- value!              \
* (add) target! addend -- result     \
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
");

    assert(list_length(stmt_list) == 10);

    printf("</parser_test>\n");
}
