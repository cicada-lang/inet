#include "index.h"

void
hash_test(void) {
    printf("<hash_test>\n");

    hash_t *hash = hash_new();

    void *k1 = (void *) 1;
    void *k2 = (void *) 2;
    void *k3 = (void *) 3;

    assert(hash_set(hash, k1, string_dup("a")));
    assert(hash_set(hash, k2, string_dup("b")));
    assert(hash_set(hash, k3, string_dup("c")));

    assert(string_equal(hash_get(hash, k1), "a"));
    assert(string_equal(hash_get(hash, k2), "b"));
    assert(string_equal(hash_get(hash, k3), "c"));

    assert(!hash_set(hash, k2, string_dup("d")));
    assert(string_equal(hash_get(hash, k2), "b"));

    hash_put(hash, k2, string_dup("d"));
    assert(string_equal(hash_get(hash, k2), "d"));

    hash_destroy(&hash);

    printf("</hash_test>\n");
}
