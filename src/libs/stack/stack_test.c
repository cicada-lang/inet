#include "index.h"

void
stack_test(void) {
    printf("<stack>");

    stack_t *stack = stack_new(100);
    assert(stack);
    assert(stack_size(stack) == 100);
    assert(stack_length(stack) == 0);
    assert(stack_is_empty(stack));

    stack_set_item_destructor(stack, (stack_item_destructor_t *) string_destroy);

    stack_destroy(&stack);

    printf("</stack>\n");
}
