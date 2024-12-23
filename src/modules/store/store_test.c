#include "index.h"

void
store_test(void) {
    printf("<store_test>\n");

    char *base = dirname(string_copy(__FILE__));
    store_t *store = store_new(base);

    printf("store base: %s\n", store_base(store));

    assert(store_cache_length(store) == 0);

    assert(store_has(store, "abc.txt"));
    assert(store_has(store, "123.txt"));
    assert(!store_has(store, "xyz.txt"));
    assert(!store_has(store, "456.txt"));

    assert(store_cache_length(store) == 2);

    {
        blob_t *blob = store_get(store, "abc.txt");
        assert(blob_bytes(blob)[0] == 'a');
        assert(blob_bytes(blob)[1] == 'b');
        assert(blob_bytes(blob)[2] == 'c');
    }

    {
        blob_t *blob = store_get(store, "123.txt");
        assert(blob_bytes(blob)[0] == '1');
        assert(blob_bytes(blob)[1] == '2');
        assert(blob_bytes(blob)[2] == '3');
    }

    assert(store_cache_length(store) == 2);
    store_purge_cache(store);
    assert(store_cache_length(store) == 0);

    {
        blob_t *blob = store_get(store, "abc.txt");
        assert(blob_bytes(blob)[0] == 'a');
        assert(blob_bytes(blob)[1] == 'b');
        assert(blob_bytes(blob)[2] == 'c');
    }

    {
        blob_t *blob = store_get(store, "123.txt");
        assert(blob_bytes(blob)[0] == '1');
        assert(blob_bytes(blob)[1] == '2');
        assert(blob_bytes(blob)[2] == '3');
    }

    assert(store_cache_length(store) == 2);

    store_destroy(&store);

    printf("</store_test>\n");
}
