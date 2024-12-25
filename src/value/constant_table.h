#pragma once

struct constant_table_entry_t {
    const char *name;
    value_t value;
};

typedef struct constant_table_entry_t constant_table_entry_t;

extern constant_table_entry_t constant_table[];

bool string_is_constant_value(const char *string);
value_t string_to_constant_value(const char *string);
