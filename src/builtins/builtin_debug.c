#include "index.h"

void
builtin_debug(vm_t *vm) {
    fprintf(vm->out, "[debug] debug start\n");
    debug_start(vm);
    fprintf(vm->out, "[debug] debug end\n");
    fprintf(vm->out, "\n");    
}
