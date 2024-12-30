#include "index.h"

void
x_swap(vm_t *vm) {
    wire_t *y = stack_pop(vm->value_stack);
    wire_t *x = stack_pop(vm->value_stack);

    stack_push(vm->value_stack, y);
    stack_push(vm->value_stack, x);
}

void
x_rot(vm_t *vm) {
    wire_t *z = stack_pop(vm->value_stack);
    wire_t *y = stack_pop(vm->value_stack);
    wire_t *x = stack_pop(vm->value_stack);

    stack_push(vm->value_stack, y);
    stack_push(vm->value_stack, z);
    stack_push(vm->value_stack, x);
}
