#include "index.h"

void
call_constant(vm_t *vm, const constant_def_t *def) {
    stack_push(vm->value_stack, def->value);
    return;
}
