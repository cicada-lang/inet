#include "index.h"

void
stack_test(void) {
    printf("<stack>");

    stack_t *stack = stack_new(100);
    assert(stack);
    assert(stack_size(stack) == 100);
    assert(stack_length(stack) == 0);
    assert(stack_is_empty(stack));

    stack_destroy(&stack);

    printf("</stack>\n");
}
