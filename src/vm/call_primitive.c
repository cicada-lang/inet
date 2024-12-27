#include "index.h"

void
call_primitive(vm_t *vm, const primitive_def_t *def) {
    def->primitive_fn(vm);
    return;
}
