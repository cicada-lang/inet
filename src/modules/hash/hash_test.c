#include "index.h"

void
hash_test(void) {
    printf("<hash_test>\n");

    {
        hash_t *hash = hash_new();
        assert(hash_length(hash) == 0);

        void *k1 = (void *) 1;
        void *k2 = (void *) 2;
        void *k3 = (void *) 3;

        assert(hash_set(hash, k1, string_copy("a")));
        assert(hash_set(hash, k2, string_copy("b")));
        assert(hash_set(hash, k3, string_copy("c")));
        assert(hash_length(hash) == 3);

        assert(string_equal(hash_get(hash, k1), "a"));
        assert(string_equal(hash_get(hash, k2), "b"));
        assert(string_equal(hash_get(hash, k3), "c"));

        assert(!hash_set(hash, k2, string_copy("d")));
        assert(string_equal(hash_get(hash, k2), "b"));

        hash_put(hash, k2, string_copy("d"));
        assert(string_equal(hash_get(hash, k2), "d"));

        hash_delete(hash, k2);
        assert(!hash_get(hash, k2));
        assert(hash_length(hash) == 2);

        hash_purge(hash);
        assert(hash_length(hash) == 0);
        hash_destroy(&hash);
    }

    {
        hash_t *hash = hash_new();

        size_t length = 1000 * 1000;
        for (size_t i = 0; i < length; i++)
            hash_set(hash, (void *) i, (void *) i);

        for (size_t i = 0; i < length; i++)
            assert(hash_get(hash, (void *) i) == (void *) i);

        hash_report(hash);

        hash_purge(hash);
        assert(hash_length(hash) == 0);
        hash_destroy(&hash);
    }

    {
        hash_t *hash = hash_new();

        size_t length = 1000 * 1000;
        for (size_t i = 0; i < length; i++)
            hash_set(hash, (void *) (uint64_t) rand(), (void *) i);

        hash_report(hash);

        hash_purge(hash);
        assert(hash_length(hash) == 0);
        hash_destroy(&hash);
    }

    {
        hash_t *hash = hash_new();
        hash_set_hash_fn(hash, (hash_fn_t *) string_bernstein_hash);
        hash_set_destroy_fn(hash, (destroy_fn_t *) string_destroy);
        hash_set_key_destroy_fn(hash, (destroy_fn_t *) string_destroy);
        hash_set_key_equal_fn(hash, (equal_fn_t *) string_equal);

        //  Insert some entries
        assert(hash_set(hash, string_copy("DEADBEEF"), string_copy("dead beef")));
        assert(hash_set(hash, string_copy("ABADCAFE"), string_copy("a bad cafe")));
        assert(hash_set(hash, string_copy("C0DEDBAD"), string_copy("coded bad")));
        assert(hash_set(hash, string_copy("DEADF00D"), string_copy("dead food")));
        assert(hash_length(hash) == 4);

        //  Look for existing entries
        assert(string_equal(hash_get(hash, "DEADBEEF"), "dead beef"));
        assert(string_equal(hash_get(hash, "ABADCAFE"), "a bad cafe"));
        assert(string_equal(hash_get(hash, "C0DEDBAD"), "coded bad"));
        assert(string_equal(hash_get(hash, "DEADF00D"), "dead food"));

        //  Look for non-existent entries
        assert(!hash_get(hash, "foo"));

        //  Try to insert duplicate entries
        assert(!hash_set(hash, string_copy("DEADBEEF"), string_copy("foo")));
        assert(string_equal(hash_get(hash, "DEADBEEF"), "dead beef"));

        //  Put duplicate entries
        hash_put(hash, string_copy("DEADBEEF"), string_copy("foo"));
        assert(string_equal(hash_get(hash, "DEADBEEF"), "foo"));

        //  Delete entries
        hash_delete(hash, "DEADBEEF");
        assert(!hash_get(hash, "DEADBEEF"));
        hash_delete(hash, "ABADCAFE");
        assert(!hash_get(hash, "ABADCAFE"));
        assert(hash_length(hash) == 2);

        hash_purge(hash);
        assert(hash_length(hash) == 0);
        hash_destroy(&hash);
    }

    {
        hash_t *hash = hash_new();
        hash_set_hash_fn(hash, (hash_fn_t *) string_bernstein_hash);
        hash_set_destroy_fn(hash, (destroy_fn_t *) string_destroy);
        hash_set_key_destroy_fn(hash, (destroy_fn_t *) string_destroy);
        hash_set_key_equal_fn(hash, (equal_fn_t *) string_equal);

        assert(!hash_first(hash));

        //  Insert some entries
        assert(hash_set(hash, string_copy("DEADBEEF"), string_copy("dead beef")));
        assert(hash_set(hash, string_copy("ABADCAFE"), string_copy("a bad cafe")));
        assert(hash_set(hash, string_copy("C0DEDBAD"), string_copy("coded bad")));
        assert(hash_set(hash, string_copy("DEADF00D"), string_copy("dead food")));
        assert(hash_length(hash) == 4);

        {
            list_t *list = hash_value_list(hash);
            char *value = list_first(list);
            while (value) {
                printf("value: %s\n", value);
                value = list_next(list);
            }
            printf("\n");
            list_destroy(&list);
        }

        {
            char *value = hash_first(hash);
            while (value) {
                printf("value: %s\n", value);
                value = hash_next(hash);
            }
            printf("\n");
        }

        hash_purge(hash);
        assert(hash_length(hash) == 0);
        hash_destroy(&hash);
    }

    printf("</hash_test>\n");
}
