#include "index.h"

void x_define_function(vm_t *vm) {
    token_t *token = list_shift(vm->token_list);
    function_t *function = compile_function(vm);
    define_function(vm->mod, token->string, function);
    token_destroy(&token);
}
