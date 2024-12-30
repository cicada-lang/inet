#include "index.h"

function_ctx_t *
function_ctx_new(void) {
    function_ctx_t *self = new(function_ctx_t);
    self->local_index_hash = hash_new_of_string_key();
    return self;
}

void
function_ctx_destroy(function_ctx_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        function_ctx_t *self = *self_pointer;
        hash_destroy(&self->local_index_hash);
        free(self);
        *self_pointer = NULL;
    }
}
