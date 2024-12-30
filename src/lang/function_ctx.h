#pragma once

struct function_ctx_t {
    hash_t *local_index_hash;
};

function_ctx_t *function_ctx_new(void);
void function_ctx_destroy(function_ctx_t **self_pointer);
