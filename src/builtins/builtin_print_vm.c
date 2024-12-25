#include "index.h"

void
builtin_print_vm(vm_t *vm) {
    vm_print(vm, vm->out);
    fprintf(vm->out, "\n");
}
