#include "index.h"

static void
define_builtin(mod_t *mod, const char *name, builtin_t *builtin) {
    mod_define(mod, (spec_t *) builtin_spec_new(name, builtin));
}

void
import_builtins(mod_t *mod) {
    define_builtin(mod, "@swap", builtin_swap);
    define_builtin(mod, "@rot", builtin_rot);

    define_builtin(mod, "@wire/connect", builtin_wire_connect);
    define_builtin(mod, "@wire/print-net", builtin_wire_print_net);
    define_builtin(mod, "@wire/pair", builtin_wire_pair);

    define_builtin(mod, "@worker/interact", builtin_worker_interact);
    define_builtin(mod, "@worker/print", builtin_worker_print);
    define_builtin(mod, "@worker/print-value-stack", builtin_worker_print_value_stack);
    define_builtin(mod, "@worker/print-return-stack", builtin_worker_print_return_stack);
}
