#include "index.h"

void
x_connect(vm_t *vm) {
    vm_connect_top_wire_pair(vm);
}

void
x_wire_print_net(vm_t *vm) {
    wire_t *wire = stack_top(vm->value_stack);
    wire_print_net(wire, stdout);
    fprintf(stdout, "\n");
}

void
x_wire_pair(vm_t *vm) {
    wire_t *first_wire = wire_new();
    wire_t *second_wire = wire_new();

    first_wire->opposite = second_wire;
    second_wire->opposite = first_wire;

    stack_push(vm->value_stack, first_wire);
    stack_push(vm->value_stack, second_wire);
}

void
x_run(vm_t *vm) {
    run_net(vm);
}

void
x_debug(vm_t *vm) {
    fprintf(stdout, "[debug] debug start\n");
    debug_start(vm);
    fprintf(stdout, "[debug] debug end\n");
    fprintf(stdout, "\n");
}

void
define_node(mod_t *mod, const char *name, list_t *input_token_list, list_t *output_token_list) {
    // check_name_not_defined(vm, name, head_token);

    size_t input_arity = list_length(input_token_list);
    size_t output_arity = list_length(output_token_list);
    node_def_t *node_def = node_def_new(name, input_arity, output_arity);
    def_t *def = def_from_node_def(node_def);

    port_index_t index = 0;

    token_t *input_token = list_first(input_token_list);
    while (input_token) {
        def->as_node_def->port_defs[index] =
            port_def_from_name(input_token->string);
        input_token = list_next(input_token_list);
        index++;
    }

    token_t *output_token = list_first(output_token_list);
    while (output_token) {
        def->as_node_def->port_defs[index] =
            port_def_from_name(output_token->string);
        output_token = list_next(output_token_list);
        index++;
    }

    mod_define(mod, def);
    return;
}

void
x_define_node(vm_t *vm) {
    (void) vm;
    fprintf(stdout, "x_define_node\n");
}
