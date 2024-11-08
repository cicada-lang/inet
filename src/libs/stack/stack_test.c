#include "index.h"

void
stack_test(void) {
    printf("<stack>");

    stack_t *stack = stack_new(100);
    assert(stack);
    assert(stack_size(stack) == 100);
    assert(stack_length(stack) == 0);

    printf("</stack>\n");
}
