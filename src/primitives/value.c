#include "index.h"

value_t x_eq(value_t x, value_t y) {
    return xbool(x == y);
}

void x_dup(vm_t *vm) {
    value_t x = stack_pop(vm->value_stack);
    stack_push(vm->value_stack, x);
    stack_push(vm->value_stack, x);
}

void x_swap(vm_t *vm) {
    value_t y = stack_pop(vm->value_stack);
    value_t x = stack_pop(vm->value_stack);
    stack_push(vm->value_stack, y);
    stack_push(vm->value_stack, x);
}

void x_drop(vm_t *vm) {
    (void) stack_pop(vm->value_stack);
}

void x_rot(vm_t *vm) {
    value_t z = stack_pop(vm->value_stack);
    value_t y = stack_pop(vm->value_stack);
    value_t x = stack_pop(vm->value_stack);
    stack_push(vm->value_stack, y);
    stack_push(vm->value_stack, z);
    stack_push(vm->value_stack, x);
}

void x_over(vm_t *vm) {
    value_t y = stack_pop(vm->value_stack);
    value_t x = stack_pop(vm->value_stack);
    stack_push(vm->value_stack, x);
    stack_push(vm->value_stack, y);
    stack_push(vm->value_stack, x);
}

void x_tuck(vm_t *vm) {
    value_t y = stack_pop(vm->value_stack);
    value_t x = stack_pop(vm->value_stack);
    stack_push(vm->value_stack, y);
    stack_push(vm->value_stack, x);
    stack_push(vm->value_stack, y);
}
