#include "index.h"

void
sexp_test(void) {
    printf("<sexp_test>\n");


    sexp_print(sexp_parse("(a b c)"), stdout);
    printf("\n");

    sexp_print(sexp_parse("((a \"b\" c) (a . c) (1 1.2))"), stdout);
    printf("\n");

    printf("</sexp_test>\n");
}
