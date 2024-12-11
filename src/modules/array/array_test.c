#include "index.h"

void
array_test(void) {
    printf("<array_test>\n");

    array_t *array = array_new_with(
        100, (destroy_t *) string_destroy);

    assert(array);
    assert(array_size(array) == 100);
    assert(array_length(array) == 0);
    assert(array_is_empty(array));

    char *cheese = string_dup("boursin");
    char *bread = string_dup("baguette");
    char *wine = string_dup("bordeaux");

    array_push(array, cheese);
    assert(array_length(array) == 1);
    assert(!array_is_empty(array));

    array_push(array, bread);
    assert(array_length(array) == 2);
    assert(!array_is_empty(array));

    array_push(array, wine);
    assert(array_length(array) == 3);
    assert(!array_is_empty(array));

    assert(array_pick(array, 0) == wine);
    assert(array_pick(array, 1) == bread);
    assert(array_pick(array, 2) == cheese);

    assert(array_get(array, 2) == wine);
    assert(array_get(array, 1) == bread);
    assert(array_get(array, 0) == cheese);

    assert(array_pop(array) == wine);
    assert(array_pop(array) == bread);
    assert(array_pop(array) == cheese);

    assert(array_length(array) == 0);
    assert(array_is_empty(array));

    array_push(array, cheese);
    array_push(array, bread);
    array_push(array, wine);
    assert(array_length(array) == 3);

    array_purge(array);
    assert(array_length(array) == 0);
    assert(array_is_empty(array));

    array_destroy(&array);
    assert(array == NULL);

    {
        char *cheese = string_dup("boursin");
        char *bread = string_dup("baguette");
        char *wine = string_dup("bordeaux");

        array_t *array = array_new_with(
            3, (destroy_t *) string_destroy);

        assert(!array_is_full(array));

        array_push(array, cheese);  assert(!array_is_full(array));
        array_push(array, bread);   assert(!array_is_full(array));
        array_push(array, wine);    assert(array_is_full(array));

        // array_destroy(&array);
        // assert(array == NULL);
    }

    printf("</array_test>\n");
}
