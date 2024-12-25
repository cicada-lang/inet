#include "index.h"

void
builtin_wire_pair(vm_t *vm) {
    wire_t *first_wire = wire_new();
    wire_t *second_wire = wire_new();

    first_wire->opposite = second_wire;
    second_wire->opposite = first_wire;

    stack_push(vm->value_stack, first_wire);
    stack_push(vm->value_stack, second_wire);
}
