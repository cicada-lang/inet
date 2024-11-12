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
    // * (zero) -- value!
    // * (add1) prev -- value!
    // * (add) target! addend -- result

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
        spec->port_specs[2] = port_spec_new("result", false);
        mod_define(mod, (spec_t *) spec);
    }

    // ! (zero)-(add)
    //   (add)-addend result-(add)

    // ! (add1)-(add)
    //   (add)-addend (add1)-prev add
    //   add1 result-(add)

    {
        program_t *program = program_new();
        emit_get_free_wire(mod, program, "add", "addend");
        emit_reconnect_free_wire(mod, program, "add", "result");
        mod_define_rule(mod, "zero", "add", program);
    }

    {
        program_t *program = program_new();
        emit_get_free_wire(mod, program, "add", "addend");
        emit_get_free_wire(mod, program, "add1", "prev");
        emit_call(mod, program, "add");
        emit_call(mod, program, "add1");
        emit_reconnect_free_wire(mod, program, "add", "result");
        mod_define_rule(mod, "add1", "add", program);
    }
}
