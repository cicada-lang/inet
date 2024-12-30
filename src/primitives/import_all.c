#include "index.h"

static void
define_primitive(mod_t *mod, const char *name, primitive_vm_fn_t *primitive) {
    mod_define(mod, def_from_primitive_def(primitive_def_new(name, primitive)));
}

void
import_all(mod_t *mod) {
    define_primitive(mod, "swap", x_swap);
    define_primitive(mod, "rot", x_rot);

    define_primitive(mod, "connect", x_connect);
    define_primitive(mod, "wire-print-net", x_wire_print_net);
    define_primitive(mod, "wire-pair", x_wire_pair);

    define_primitive(mod, "run", x_run);
    define_primitive(mod, "print-vm", x_print_vm);
    define_primitive(mod, "print-value-stack", x_print_value_stack);
    define_primitive(mod, "print-return-stack", x_print_return_stack);

    define_primitive(mod, "debug", x_debug);
}
