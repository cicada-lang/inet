#include "index.h"

void x_define_constant(vm_t *vm) {
    token_t *token = list_shift(vm->token_list);
    value_t value = stack_pop(vm->value_stack);
    define_constant(vm->mod, token->string, value);
    token_destroy(&token);
}
