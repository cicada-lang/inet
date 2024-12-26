#include "index.h"

void
primitive_print_value_stack(vm_t *vm) {
    vm_print_value_stack(vm, vm->out);
    fprintf(vm->out, "\n");
}
