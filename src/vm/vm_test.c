#include "index.h"

static void mod_import_nat(mod_t *mod);

void
vm_test(void) {
    printf("<vm_test>\n");

    mod_t *mod = mod_new("vm_test", "");
    mod_import_nat(mod);

    vm_t *vm = vm_new(mod);

    function_t *function = function_new();
    emit_call(mod, function, "zero");
    emit_call(mod, function, "add1");
    emit_call(mod, function, "add1");
    emit_call(mod, function, "zero");
    emit_call(mod, function, "add1");
    emit_call(mod, function, "add1");
    emit_call(mod, function, "add");
    function_build(function);

    frame_t *frame = frame_new(function);
    stack_push(vm->return_stack, frame);

    vm->log_level = 1;
    run_vm_until_until(vm, 0);
    run_net(vm);

    vm_destroy(&vm);
    mod_destroy(&mod);

    printf("</vm_test>\n");
}

void
mod_import_nat(mod_t *mod) {
    // * (zero) -> value!
    // * (add1) prev -> value!
    // * (add) addend target! -> result

    {
        def_t *def = def_from_node_def(node_def_new("zero", 0, 1));
        def->as_node_def->port_defs[0] = port_def_new("value", true);
        mod_define(mod, def);
    }

    {
        def_t *def = def_from_node_def(node_def_new("add1", 1, 1));
        def->as_node_def->port_defs[0] = port_def_new("prev", false);
        def->as_node_def->port_defs[1] = port_def_new("value", true);
        mod_define(mod, def);
    }

    {
        def_t *def = def_from_node_def(node_def_new("add", 2, 1));
        def->as_node_def->port_defs[0] = port_def_new("addend", false);
        def->as_node_def->port_defs[1] = port_def_new("target", true);
        def->as_node_def->port_defs[2] = port_def_new("result", false);
        mod_define(mod, def);
    }

    // ! (zero)-(add)
    //   (add)-addend result-(add)

    // ! (add1)-(add)
    //   (add)-addend (add1)-prev add
    //   add1 result-(add)

    {
        function_t *function = function_new();
        emit_use_free_wire(mod, function, "add", "addend");
        emit_reconnect_free_wire(mod, function, "add", "result");
        function_build(function);
        mod_define_rule(mod, "zero", "add", function);
    }

    {
        function_t *function = function_new();
        emit_use_free_wire(mod, function, "add", "addend");
        emit_use_free_wire(mod, function, "add1", "prev");
        emit_call(mod, function, "add");
        emit_call(mod, function, "add1");
        emit_reconnect_free_wire(mod, function, "add", "result");
        function_build(function);
        mod_define_rule(mod, "add1", "add", function);
    }
}
