#include "index.h"

void
stack_test(void) {
    printf("<stack_test>\n");

    stack_t *stack = stack_new_with((destroy_fn_t *) string_destroy);

    assert(stack);

    assert(stack_length(stack) == 0);
    assert(stack_is_empty(stack));

    char *cheese = string_copy("boursin");
    char *bread = string_copy("baguette");
    char *wine = string_copy("bordeaux");

    stack_push(stack, cheese);
    assert(stack_top(stack) == cheese);
    assert(stack_length(stack) == 1);
    assert(!stack_is_empty(stack));

    stack_push(stack, bread);
    assert(stack_top(stack) == bread);
    assert(stack_length(stack) == 2);
    assert(!stack_is_empty(stack));

    stack_push(stack, wine);
    assert(stack_top(stack) == wine);
    assert(stack_length(stack) == 3);
    assert(!stack_is_empty(stack));

    assert(stack_pick(stack, 0) == wine);
    assert(stack_pick(stack, 1) == bread);
    assert(stack_pick(stack, 2) == cheese);

    assert(stack_get(stack, 2) == wine);
    assert(stack_get(stack, 1) == bread);
    assert(stack_get(stack, 0) == cheese);

    assert(stack_pop(stack) == wine);
    assert(stack_pop(stack) == bread);
    assert(stack_pop(stack) == cheese);

    assert(stack_length(stack) == 0);
    assert(stack_is_empty(stack));

    stack_push(stack, cheese);
    stack_push(stack, bread);
    stack_push(stack, wine);
    assert(stack_length(stack) == 3);

    stack_purge(stack);
    assert(stack_length(stack) == 0);
    assert(stack_is_empty(stack));

    stack_destroy(&stack);
    assert(stack == NULL);

    printf("</stack_test>\n");
}
