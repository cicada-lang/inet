#include "index.h"

static void
define_builtin(mod_t *mod, const char *name, builtin_fn_t *builtin) {
    mod_define(mod, (spec_t *) builtin_spec_new(name, builtin));
}

void
import_builtins(mod_t *mod) {
    define_builtin(mod, "swap", builtin_swap);
    define_builtin(mod, "rot", builtin_rot);

    define_builtin(mod, "connect", builtin_connect);
    define_builtin(mod, "wire-print-net", builtin_wire_print_net);
    define_builtin(mod, "wire-pair", builtin_wire_pair);

    define_builtin(mod, "run", builtin_run);
    define_builtin(mod, "print-vm", builtin_print_vm);
    define_builtin(mod, "print-value-stack", builtin_print_value_stack);
    define_builtin(mod, "print-return-stack", builtin_print_return_stack);

    define_builtin(mod, "debug", builtin_debug);
}
