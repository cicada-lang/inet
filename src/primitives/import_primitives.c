#include "index.h"

static void
define_primitive(mod_t *mod, const char *name, primitive_vm_fn_t *primitive) {
    mod_define(mod, def_from_primitive_def(primitive_def_new(name, primitive)));
}

void
import_primitives(mod_t *mod) {
    define_primitive(mod, "swap", primitive_swap);
    define_primitive(mod, "rot", primitive_rot);

    define_primitive(mod, "connect", primitive_connect);
    define_primitive(mod, "wire-print-net", primitive_wire_print_net);
    define_primitive(mod, "wire-pair", primitive_wire_pair);

    define_primitive(mod, "run", primitive_run);
    define_primitive(mod, "print-vm", primitive_print_vm);
    define_primitive(mod, "print-value-stack", primitive_print_value_stack);
    define_primitive(mod, "print-return-stack", primitive_print_return_stack);

    define_primitive(mod, "debug", primitive_debug);
}
