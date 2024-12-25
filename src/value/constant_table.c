#include "index.h"

constant_table_entry_t constant_table[] = {
    { "null", xnull },
    { "true", xtrue },
    { "false", xfalse },
};

bool
string_is_constant_value(const char *string) {
    size_t length = sizeof(constant_table) / sizeof(constant_table_entry_t);
    for (size_t i = 0; i < length; i++) {
        if (string_equal(string, constant_table[i].name)) {
            return true;
        }
    }

    return false;
}

value_t
string_to_constant_value(const char *string) {
    size_t length = sizeof(constant_table) / sizeof(constant_table_entry_t);
    for (size_t i = 0; i < length; i++) {
        if (string_equal(string, constant_table[i].name)) {
            return constant_table[i].value;
        }
    }

    assert(false);
}
