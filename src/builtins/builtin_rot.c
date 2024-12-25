#include "index.h"

void
builtin_rot(vm_t *vm) {
    wire_t *third = stack_pop(vm->value_stack);
    wire_t *second = stack_pop(vm->value_stack);
    wire_t *first = stack_pop(vm->value_stack);

    stack_push(vm->value_stack, second);
    stack_push(vm->value_stack, third);
    stack_push(vm->value_stack, first);
}
