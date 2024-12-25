#include "index.h"

void
builtin_print_return_stack(vm_t *vm) {
    vm_print_return_stack(vm, vm->out);
    fprintf(vm->out, "\n");
}
