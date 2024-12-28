#include "index.h"

function_def_t *
function_def_new(const char *name, function_t *function) {
    function_def_t *self = new(function_def_t);
    self->name = string_copy(name);
    self->function = function;
    return self;
}

void
function_def_destroy(function_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        function_def_t *self = *self_pointer;
        string_destroy(&self->name);
        function_destroy(&self->function);
        free(self);
        *self_pointer = NULL;
    }
}
