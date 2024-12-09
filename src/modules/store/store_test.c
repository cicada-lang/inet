#include "index.h"

void
store_test(void) {
    printf("<store_test>\n");

    char *base = dirname(string_dup(__FILE__));
    store_t *store = store_new(base);

    printf("store base: %s\n", store_base(store));

    assert(store_cache_size(store) == 0);

    assert(store_has(store, "abc.txt"));
    assert(store_has(store, "123.txt"));
    assert(!store_has(store, "xyz.txt"));
    assert(!store_has(store, "456.txt"));

    assert(store_cache_size(store) == 2);

    {
        uint8_t *bytes = store_get(store, "abc.txt");
        assert(bytes[0] == 'a');
        assert(bytes[1] == 'b');
        assert(bytes[2] == 'c');
    }

    {
        uint8_t *bytes = store_get(store, "123.txt");
        assert(bytes[0] == '1');
        assert(bytes[1] == '2');
        assert(bytes[2] == '3');
    }

    assert(store_cache_size(store) == 2);
    store_purge_cache(store);
    assert(store_cache_size(store) == 0);

    {
        uint8_t *bytes = store_get(store, "abc.txt");
        assert(bytes[0] == 'a');
        assert(bytes[1] == 'b');
        assert(bytes[2] == 'c');
    }

    {
        uint8_t *bytes = store_get(store, "123.txt");
        assert(bytes[0] == '1');
        assert(bytes[1] == '2');
        assert(bytes[2] == '3');
    }

    assert(store_cache_size(store) == 2);

    store_destroy(&store);

    printf("</store_test>\n");
}
