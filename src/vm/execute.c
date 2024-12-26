#include "index.h"

static void node_apply_input_ports(vm_t *vm, node_t *node);
static void node_return_output_ports(vm_t *vm, node_t *node);

void
execute(vm_t *vm, frame_t *frame, op_t *unknown_op) {
    switch (unknown_op->kind) {
    case CALL_BUILTIN_OP: {
        call_builtin_op_t *op = (call_builtin_op_t *) unknown_op;
        op->builtin_def->builtin_fn(vm);
        return;
    }

    case CALL_PROGRAM_OP: {
        call_program_op_t *op = (call_program_op_t *) unknown_op;
        frame_t *frame = frame_new(op->program_def->program);
        stack_push(vm->return_stack, frame);
        return;
    }

    case CALL_NODE_OP: {
        call_node_op_t *op = (call_node_op_t *) unknown_op;        
        node_t *node = node_new(op->node_def, ++vm->node_id_count);
        node_apply_input_ports(vm, node);
        node_return_output_ports(vm, node);
        return;
    }

    case CONNECT_OP: {
        vm_connect_top_wire_pair(vm);
        return;
    }

    case GET_FREE_WIRE_OP: {
        use_free_wire_op_t *op = (use_free_wire_op_t *) unknown_op;
        wire_t *free_wire = frame_use_free_wire(frame, op->node_def, op->index);
        assert(free_wire);
        stack_push(vm->value_stack, free_wire);
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
