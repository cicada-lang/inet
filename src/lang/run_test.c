#include "index.h"

void
run_test(void) {
    printf("<run_test>\n");

    const char *text = "\
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
";

    worker_t *worker = run_text(text);
    worker_destroy(&worker);

    printf("</run_test>\n");
}
