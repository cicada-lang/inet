#include "index.h"

void
list_test(void) {
    printf("<list_test>\n");

    list_t *list = list_new();
    assert(list);
    assert(list_length(list) == 0);

    assert(list_first(list) == NULL);
    assert(list_last(list) == NULL);

    assert(list_next(list) == NULL);
    assert(list_prev(list) == NULL);

    assert(list_pop(list) == NULL);
    assert(list_shift(list) == NULL);

    //  Three values we'll use as test data
    //  List values are void *, not particularly strings
    char *cheese = string_copy("cheese");
    char *bread = string_copy("bread");
    char *wine = string_copy("wine");

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

        assert(list_first(list) == cheese);
        assert(list_next(list) == bread);

        assert(list_first(list) == cheese);
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
        assert(list_first(list) == bread);

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

        assert(list_first(list) == cheese);
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

        assert(list_last(list) == wine);
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

        list_set_destroy_fn(list, (destroy_fn_t *) string_destroy);

        list_purge(list);
        assert(list_length(list) == 0);

        list_destroy(&list);
        assert(list == NULL);
    }

    {
        char *a = string_copy("a");
        char *b = string_copy("b");
        char *c = string_copy("c");

        list_t *list = list_new_with((destroy_fn_t *) string_destroy);

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

        list_set_equal_fn(list, (equal_fn_t *) string_equal);

        assert(list_has(list, "a"));
        assert(list_has(list, "b"));
        assert(list_has(list, "c"));

        assert(!list_has(list, "A"));
        assert(!list_has(list, "B"));
        assert(!list_has(list, "C"));

        assert(!list_find(list, "A"));
        assert(!list_find(list, "B"));
        assert(!list_find(list, "C"));

        list_set_equal_fn(list, (equal_fn_t *) string_equal_mod_case);

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


    {
        assert(list_copy(NULL) == NULL);
    }

    {
        char *a = string_copy("a");
        char *b = string_copy("b");
        char *c = string_copy("c");

        list_t *list = list_new_with((destroy_fn_t *) string_destroy);
        list_set_equal_fn(list, (equal_fn_t *) string_equal_mod_case);
        list_set_copy_fn(list, (copy_fn_t *) string_copy);

        list_push(list, a);
        list_push(list, b);
        list_push(list, c);

        list_t *copy = list_copy(list);
        list_set_destroy_fn(copy, (destroy_fn_t *) string_destroy);
        list_set_equal_fn(copy, (equal_fn_t *) string_equal_mod_case);

        list_destroy(&list);

        assert(list_has(copy, "a"));
        assert(list_has(copy, "b"));
        assert(list_has(copy, "c"));

        assert(list_has(copy, "A"));
        assert(list_has(copy, "B"));
        assert(list_has(copy, "C"));

        list_destroy(&copy);
        assert(copy == NULL);
    }

    {
        // list_remove with destroy_fn

        char *a = string_copy("a");
        char *b = string_copy("b");
        char *c = string_copy("c");

        list_t *list = list_new();
        list_set_destroy_fn(list, (destroy_fn_t *) string_destroy);
        list_set_equal_fn(list, (equal_fn_t *) string_equal_mod_case);

        list_push(list, a);
        list_push(list, b);
        list_push(list, c);

        list_remove(list, "B");

        assert(list_has(list, "A"));
        assert(!list_has(list, "B"));
        assert(list_has(list, "C"));

        list_destroy(&list);
        assert(list == NULL);
    }

    printf("</list_test>\n");
}
