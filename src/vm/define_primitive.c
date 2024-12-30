#include "index.h"

void
define_primitive_vm_fn(mod_t *mod, const char *name, primitive_vm_fn_t *primitive) {
    mod_define(mod, def_from_primitive_def(primitive_def_new(name, primitive)));
}
