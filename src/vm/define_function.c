#include "index.h"

void
define_function(mod_t *mod, const char *name, function_t *function) {
    mod_define(mod, def_from_function_def(function_def_new(name, function)));
}
