#include "index.h"

void
mod_test(void) {
    printf("<mod_test>\n");

    mod_t *mod = mod_new();
    mod_import_nat(mod);

    mod_destroy(&mod);

    printf("</mod_test>\n");
}

void mod_import_nat(mod_t *mod) {
    {
        node_spec_t *spec = node_spec_new("zero", 0, 1);
        spec->port_specs[0] = port_spec_new("value", true);
        mod_define(mod, (spec_t *) spec);
    }

    {
        node_spec_t *spec = node_spec_new("add1", 1, 1);
        spec->port_specs[0] = port_spec_new("prev", false);
        spec->port_specs[1] = port_spec_new("value", true);
        mod_define(mod, (spec_t *) spec);
    }

    {
        node_spec_t *spec = node_spec_new("add", 2, 1);
        spec->port_specs[0] = port_spec_new("target", true);
        spec->port_specs[1] = port_spec_new("addend", false);
        spec->port_specs[2] = port_spec_new("value", false);
        mod_define(mod, (spec_t *) spec);
    }
}
