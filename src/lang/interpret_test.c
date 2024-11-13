#include "index.h"

void
interpret_test(void) {
    printf("<interpret_test>\n");

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


    mod_t *mod = mod_new();
    worker_t *worker = worker_new(mod);

    worker->debug = true;

    interpret_text(worker, text);

    worker_destroy(&worker);
    mod_destroy(&mod);

    printf("</interpret_test>\n");
}
