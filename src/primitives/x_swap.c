#include "index.h"

void
x_swap(vm_t *vm) {
    wire_t *second = stack_pop(vm->value_stack);
    wire_t *first = stack_pop(vm->value_stack);

    stack_push(vm->value_stack, second);
    stack_push(vm->value_stack, first);
}
