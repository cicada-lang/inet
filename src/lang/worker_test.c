#include "index.h"

void
worker_test(void) {
    printf("<worker_test>\n");

    mod_t *mod = mod_new();

    {
        node_spec_t *node_spec = node_spec_new("zero", 0, 1);
        node_spec->port_specs[0] = port_spec_new("value", true);
        mod_define(mod, (spec_t *) node_spec);
    }

    {
        node_spec_t *node_spec = node_spec_new("add1", 1, 1);
        node_spec->port_specs[0] = port_spec_new("prev", false);
        node_spec->port_specs[1] = port_spec_new("value", true);
        mod_define(mod, (spec_t *) node_spec);
    }

    {
        node_spec_t *node_spec = node_spec_new("add", 2, 1);
        node_spec->port_specs[0] = port_spec_new("target", true);
        node_spec->port_specs[1] = port_spec_new("addend", false);
        node_spec->port_specs[2] = port_spec_new("value", false);
        mod_define(mod, (spec_t *) node_spec);
    }

    worker_t *worker = worker_new(mod);

    // TODO

    worker_destroy(&worker);
    mod_destroy(&mod);

    printf("</worker_test>\n");
}
