#include "index.h"

void
x_connect(vm_t *vm) {
    vm_connect_top_wire_pair(vm);
}

void
x_wire_print_net(vm_t *vm) {
    wire_t *wire = stack_top(vm->value_stack);
    wire_print_net(wire, stdout);
    fprintf(stdout, "\n");
}

void
x_wire_pair(vm_t *vm) {
    wire_t *first_wire = wire_new();
    wire_t *second_wire = wire_new();

    first_wire->opposite = second_wire;
    second_wire->opposite = first_wire;

    stack_push(vm->value_stack, first_wire);
    stack_push(vm->value_stack, second_wire);
}

void
x_run(vm_t *vm) {
    run_net(vm);
}

void
x_debug(vm_t *vm) {
    fprintf(stdout, "[debug] debug start\n");
    debug_start(vm);
    fprintf(stdout, "[debug] debug end\n");
    fprintf(stdout, "\n");
}
