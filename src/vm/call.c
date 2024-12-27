#include "index.h"

static void node_apply_input_ports(vm_t *vm, node_t *node);
static void node_return_output_ports(vm_t *vm, node_t *node);

void
call(vm_t *vm, const def_t *unknown_def) {
    switch (unknown_def->kind) {
    case PRIMITIVE_DEF: {
        primitive_def_t *def = (primitive_def_t *) unknown_def;
        def->primitive_fn(vm);
        return;
    }

    case PROGRAM_DEF: {
        program_def_t *def = (program_def_t *) unknown_def;
        frame_t *frame = frame_new(def->program);
        stack_push(vm->return_stack, frame);
        return;
    }

    case NODE_DEF: {
        node_def_t *def = (node_def_t *) unknown_def;
        node_t *node = node_new(def, ++vm->node_id_count);
        node_apply_input_ports(vm, node);
        node_return_output_ports(vm, node);
        return;
    }
    }
}

void
node_apply_input_ports(vm_t *vm, node_t *node) {
    for (port_index_t c = 0; c < node->def->input_arity; c++) {
        wire_t *wire = stack_pop(vm->value_stack);
        port_index_t i = node->def->input_arity - 1 - c;
        wire->node = node;
        wire->index = i;
        node->wires[i] = wire;

        vm_maybe_add_active_wire(vm, wire, wire->opposite);
    }
}

void
node_return_output_ports(vm_t *vm, node_t *node) {
    for (port_index_t c = 0; c < node->def->output_arity; c++) {
        wire_t *node_wire = wire_new();
        wire_t *free_wire = wire_new();

        node_wire->opposite = free_wire;
        free_wire->opposite = node_wire;

        port_index_t i = node->def->input_arity + c;
        node_wire->node = node;
        node_wire->index = i;
        node->wires[i] = node_wire;

        stack_push(vm->value_stack, free_wire);
    }
}
