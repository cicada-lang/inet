#include "index.h"

void
list_test(void) {
    printf("<list_test>\n");

    list_t *list = list_new();
    assert(list);
    assert(list_length(list) == 0);

    assert(list_first(list) == NULL);
    assert(list_last(list) == NULL);
    assert(list_current(list) == NULL);

    assert(list_start(list) == NULL);
    assert(list_end(list) == NULL);

    assert(list_next(list) == NULL);
    assert(list_prev(list) == NULL);

    assert(list_pop(list) == NULL);
    assert(list_shift(list) == NULL);

    //  Three items we'll use as test data
    //  List items are void *, not particularly strings
    char *cheese = string_dup("boursin");
    char *bread = string_dup("baguette");
    char *wine = string_dup("bordeaux");

    {
        list_push(list, cheese);
        assert(list_length(list) == 1);
        assert(list_has(list, cheese));
        assert(!list_has(list, bread));
        assert(!list_has(list, wine));

        list_push(list, bread);
        assert(list_length(list) == 2);
        assert(list_has(list, cheese));
        assert(list_has(list, bread));
        assert(!list_has(list, wine));

        list_push(list, wine);
        assert(list_length(list) == 3);
        assert(list_has(list, cheese));
        assert(list_has(list, bread));
        assert(list_has(list, wine));

        assert(list_first(list) == cheese);
        assert(list_next(list) == cheese);

        assert(list_start(list) == cheese);
        assert(list_last(list) == wine);
        assert(list_next(list) == bread);

        assert(list_start(list) == cheese);
        assert(list_next(list) == bread);
        assert(list_next(list) == wine);
        assert(list_next(list) == NULL);
        //  After we reach end of list, next wraps around
        assert(list_next(list) == cheese);
        assert(list_length(list) == 3);

        list_remove(list, wine);
        assert(list_length(list) == 2);

        assert(list_first(list) == cheese);
        list_remove(list, cheese);
        assert(list_length(list) == 1);
        assert(list_first(list) == bread);

        list_remove(list, bread);
        assert(list_length(list) == 0);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        assert(list_last(list) == bread);
        list_remove(list, bread);
        assert(list_last(list) == cheese);
        list_remove(list, cheese);
        assert(list_last(list) == NULL);
    }

    {
        list_unshift(list, cheese);
        assert(list_length(list) == 1);
        assert(list_first(list) == cheese);

        list_unshift(list, bread);
        assert(list_length(list) == 2);
        assert(list_start(list) == bread);
        assert(list_current(list) == bread);

        list_push(list, wine);
        assert(list_length(list) == 3);
        assert(list_first(list) == bread);

        list_pop(list);
        list_pop(list);
        list_pop(list);
    }

    {
        list_unshift(list, cheese);
        list_unshift(list, bread);
        list_unshift(list, wine);

        assert(list_shift(list) == wine);
        assert(list_shift(list) == bread);
        assert(list_shift(list) == cheese);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        list_push(list, wine);

        assert(list_start(list) == cheese);
        assert(list_next(list) == bread);
        assert(list_next(list) == wine);

        assert(list_shift(list) == cheese);
        assert(list_shift(list) == bread);
        assert(list_shift(list) == wine);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        list_push(list, wine);

        assert(list_end(list) == wine);
        assert(list_prev(list) == bread);
        assert(list_prev(list) == cheese);

        assert(list_pop(list) == wine);
        assert(list_pop(list) == bread);
        assert(list_pop(list) == cheese);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        list_push(list, wine);

        list_set_destructor(list, (destructor_t *) string_destroy);

        list_purge(list);
        assert(list_length(list) == 0);

        list_destroy(&list);
        assert(list == NULL);
    }

    printf("</list_test>\n");
}
