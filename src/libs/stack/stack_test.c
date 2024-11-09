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

    char *cheese = string_clone("boursin");
    char *bread = string_clone("baguette");
    char *wine = string_clone("bordeaux");

    stack_push(stack, cheese);
    assert(stack_length(stack) == 1);
    assert(!stack_is_empty(stack));

    stack_push(stack, bread);
    assert(stack_length(stack) == 2);
    assert(!stack_is_empty(stack));

    stack_push(stack, wine);
    assert(stack_length(stack) == 3);
    assert(!stack_is_empty(stack));

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
    // assert(cheese == NULL);
    // assert(bread == NULL);
    // assert(wine == NULL);

    stack_destroy(&stack);

    printf("</stack>\n");
}
