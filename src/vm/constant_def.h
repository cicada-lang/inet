#pragma once

struct constant_def_t {
    char *name;
    value_t value;
};

constant_def_t *constant_def_new(const char *name, value_t value);
void constant_def_destroy(constant_def_t **self_pointer);
