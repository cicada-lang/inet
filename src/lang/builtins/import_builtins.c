#include "../index.h"

void
import_builtins(mod_t *self) {
    mod_define(self, (spec_t *) builtin_spec_new("@wire/connect", builtin_wire_connect));
    mod_define(self, (spec_t *) builtin_spec_new("@wire/print-net", builtin_wire_print_net));
    mod_define(self, (spec_t *) builtin_spec_new("@worker/interact", builtin_worker_interact));
}
