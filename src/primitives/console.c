#include "index.h"

value_t x_print(value_t x) {
    value_print(x, stdout);
    return x;
}

value_t x_newline(void) {
    printf("\n");
    return NULL;
}

void
x_print_vm(vm_t *vm) {
    vm_print(vm, stdout);
    fprintf(stdout, "\n");
}

void
x_print_value_stack(vm_t *vm) {
    printf("[x_print_value_stack] 1\n");
    vm_print_value_stack(vm, stdout);
    printf("[x_print_value_stack] 2\n");
}

void
x_print_return_stack(vm_t *vm) {
    vm_print_return_stack(vm, stdout);
}
