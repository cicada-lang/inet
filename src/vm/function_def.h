#pragma once

struct function_def_t {
    char *name;
    function_t *function;
};

function_def_t *function_def_new(const char *name, function_t *function);
void function_def_destroy(function_def_t **self_pointer);
