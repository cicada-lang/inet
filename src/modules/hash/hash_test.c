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

        assert(hash_set(hash, k1, string_dup("a")));
        assert(hash_set(hash, k2, string_dup("b")));
        assert(hash_set(hash, k3, string_dup("c")));
        assert(hash_length(hash) == 3);

        assert(string_equal(hash_get(hash, k1), "a"));
        assert(string_equal(hash_get(hash, k2), "b"));
        assert(string_equal(hash_get(hash, k3), "c"));

        assert(!hash_set(hash, k2, string_dup("d")));
        assert(string_equal(hash_get(hash, k2), "b"));

        hash_put(hash, k2, string_dup("d"));
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
        for (size_t i = 0; i < length; i++) {
            // printf("i: %lu\n", i);
            hash_set(hash, (void *) i, (void *) i);
        }

        printf("hash_length(hash): %lu\n", hash_length(hash));
        assert(hash_length(hash) == length);

        hash_purge(hash);
        assert(hash_length(hash) == 0);
        hash_destroy(&hash);
    }

    printf("</hash_test>\n");
}
