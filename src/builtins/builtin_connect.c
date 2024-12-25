#include "index.h"

void
builtin_connect(vm_t *vm) {
    vm_connect_top_wire_pair(vm);
}
