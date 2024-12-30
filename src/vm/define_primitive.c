#include "index.h"

void
define_primitive_vm_fn(mod_t *mod, const char *name, primitive_vm_fn_t *primitive_vm_fn) {
    mod_define(mod, def_from_primitive_def(primitive_def_from_vm_fn(name, primitive_vm_fn)));
}

void
define_primitive_0_fn(mod_t *mod, const char *name, primitive_0_fn_t *primitive_0_fn) {
    mod_define(mod, def_from_primitive_def(primitive_def_from_0_fn(name, primitive_0_fn)));
}

void
define_primitive_1_fn(mod_t *mod, const char *name, primitive_1_fn_t *primitive_1_fn) {
    mod_define(mod, def_from_primitive_def(primitive_def_from_1_fn(name, primitive_1_fn)));
}

void
define_primitive_2_fn(mod_t *mod, const char *name, primitive_2_fn_t *primitive_2_fn) {
    mod_define(mod, def_from_primitive_def(primitive_def_from_2_fn(name, primitive_2_fn)));
}

void
define_primitive_3_fn(mod_t *mod, const char *name, primitive_3_fn_t *primitive_3_fn) {
    mod_define(mod, def_from_primitive_def(primitive_def_from_3_fn(name, primitive_3_fn)));
}

void
define_primitive_4_fn(mod_t *mod, const char *name, primitive_4_fn_t *primitive_4_fn)  {
    mod_define(mod, def_from_primitive_def(primitive_def_from_4_fn(name, primitive_4_fn)));
}
