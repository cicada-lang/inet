#include "index.h"

static void node_apply_input_ports(worker_t *worker, node_t *node);
static void node_return_output_ports(worker_t *worker, node_t *node);

void
execute(worker_t *worker, frame_t *frame, op_t *unknown_op) {
    switch (unknown_op->tag) {
    case CALL_BUILTIN_OP: {
        call_builtin_op_t *op = (call_builtin_op_t *) unknown_op;
        op->builtin_spec->builtin(worker);
        return;
    }

    case CALL_PROGRAM_OP: {
        call_program_op_t *op = (call_program_op_t *) unknown_op;
        frame_t *frame = frame_new(op->program_spec->program);
        stack_push(worker->return_stack, frame);
        return;
    }

    case CALL_NODE_OP: {
        call_node_op_t *op = (call_node_op_t *) unknown_op;        
        node_t *node = node_new(op->node_spec, ++worker->node_id_count);
        node_apply_input_ports(worker, node);
        node_return_output_ports(worker, node);
        return;
    }

    case CONNECT_OP: {
        worker_connect_top_wire_pair(worker);
        return;
    }

    case GET_FREE_WIRE_OP: {
        use_free_wire_op_t *op = (use_free_wire_op_t *) unknown_op;
        wire_t *free_wire = frame_use_free_wire(frame, op->node_spec, op->index);
        assert(free_wire);
        stack_push(worker->value_stack, free_wire);
        return;
    }
    }
}

void
node_apply_input_ports(worker_t *worker, node_t *node) {
    for (port_index_t c = 0; c < node->spec->input_arity; c++) {
        wire_t *wire = stack_pop(worker->value_stack);
        port_index_t i = node->spec->input_arity - 1 - c;
        wire->node = node;
        wire->index = i;
        node->wires[i] = wire;

        worker_maybe_add_active_wire(worker, wire, wire->opposite_wire);
    }
}

void
node_return_output_ports(worker_t *worker, node_t *node) {
    for (port_index_t c = 0; c < node->spec->output_arity; c++) {
        wire_t *node_wire = wire_new();
        wire_t *free_wire = wire_new();

        node_wire->opposite_wire = free_wire;
        free_wire->opposite_wire = node_wire;

        port_index_t i = node->spec->input_arity + c;
        node_wire->node = node;
        node_wire->index = i;
        node->wires[i] = node_wire;

        stack_push(worker->value_stack, free_wire);
    }
}
