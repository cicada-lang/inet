#include "index.h"

void
x_wire_print_net(vm_t *vm) {
    wire_t *wire = stack_top(vm->value_stack);
    wire_print_net(wire, vm->out);
    fprintf(vm->out, "\n");
}
