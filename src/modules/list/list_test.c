#include "index.h"

void
list_test(void) {
    printf("<list_test>\n");

    list_t *list = list_new();
    assert(list);
    assert(list_length(list) == 0);

    assert(list_current(list) == NULL);

    assert(list_start(list) == NULL);
    assert(list_end(list) == NULL);

    assert(list_next(list) == NULL);
    assert(list_prev(list) == NULL);

    assert(list_pop(list) == NULL);
    assert(list_shift(list) == NULL);

    //  Three items we'll use as test data
    //  List items are void *, not particularly strings
    char *cheese = string_dup("cheese");
    char *bread = string_dup("bread");
    char *wine = string_dup("wine");

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

        assert(list_next(list) == cheese);

        assert(list_start(list) == cheese);
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

        list_remove(list, cheese);
        assert(list_length(list) == 1);

        list_remove(list, bread);
        assert(list_length(list) == 0);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        list_remove(list, bread);
        list_remove(list, cheese);
    }

    {
        list_unshift(list, cheese);
        assert(list_length(list) == 1);

        list_unshift(list, bread);
        assert(list_length(list) == 2);
        assert(list_start(list) == bread);
        assert(list_current(list) == bread);

        list_push(list, wine);
        assert(list_length(list) == 3);

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

        assert(list_get(list, 0) == cheese);
        assert(list_get(list, 1) == bread);
        assert(list_get(list, 2) == wine);
        assert(list_get(list, 3) == NULL);

        assert(list_pop(list) == wine);
        assert(list_pop(list) == bread);
        assert(list_pop(list) == cheese);
    }

    {
        list_push(list, cheese);
        list_push(list, bread);
        list_push(list, wine);

        list_set_destroy_fn(list, (destroy_t *) string_destroy);

        list_purge(list);
        assert(list_length(list) == 0);

        list_destroy(&list);
        assert(list == NULL);
    }

    {
        char *a = string_dup("a");
        char *b = string_dup("b");
        char *c = string_dup("c");

        list_t *list = list_new_with((destroy_t *) string_destroy);

        list_push(list, a);
        list_push(list, b);
        list_push(list, c);

        assert(list_has(list, a));
        assert(list_has(list, b));
        assert(list_has(list, c));

        assert(!list_has(list, "a"));
        assert(!list_has(list, "b"));
        assert(!list_has(list, "c"));

        assert(!list_has(list, "A"));
        assert(!list_has(list, "B"));
        assert(!list_has(list, "C"));

        list_set_equal_fn(list, (equal_t *) string_equal);

        assert(list_has(list, "a"));
        assert(list_has(list, "b"));
        assert(list_has(list, "c"));

        assert(!list_has(list, "A"));
        assert(!list_has(list, "B"));
        assert(!list_has(list, "C"));

        assert(!list_find(list, "A"));
        assert(!list_find(list, "B"));
        assert(!list_find(list, "C"));

        list_set_equal_fn(list, (equal_t *) string_equal_mod_case);

        assert(list_has(list, "a"));
        assert(list_has(list, "b"));
        assert(list_has(list, "c"));

        assert(list_has(list, "A"));
        assert(list_has(list, "B"));
        assert(list_has(list, "C"));

        assert(list_find(list, "A") == a);
        assert(list_find(list, "B") == b);
        assert(list_find(list, "C") == c);

        list_purge(list);
        assert(list_length(list) == 0);

        list_destroy(&list);
        assert(list == NULL);
    }

    printf("</list_test>\n");
}
