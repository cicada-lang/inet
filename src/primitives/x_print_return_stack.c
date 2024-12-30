#include "index.h"

void
x_print_return_stack(vm_t *vm) {
    vm_print_return_stack(vm, vm->out);
    fprintf(vm->out, "\n");
}
