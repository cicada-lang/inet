#include "index.h"

static void node_apply_input_ports(node_t *node, worker_t *worker);
static void node_return_output_ports(node_t *node, worker_t *worker);

void
execute(op_t *unknown_op, worker_t *worker, frame_t *frame) {
    switch (unknown_op->tag) {
    case CALL_PROGRAM_OP: {
        call_program_op_t *op = (call_program_op_t *) unknown_op;
        frame_t *frame = frame_new(op->program_spec->program);
        stack_push(worker->return_stack, frame);
        return;
    }

    case CALL_NODE_OP: {
        call_node_op_t *op = (call_node_op_t *) unknown_op;
        node_t *node = node_new(op->node_spec);
        node_apply_input_ports(node, worker);
        node_return_output_ports(node, worker);
        return;
    }

    case CONNECT_OP: {
        wire_t *second_wire = stack_pop(worker->value_stack);
        wire_t *first_wire = stack_pop(worker->value_stack);

        first_wire->opposite_wire->opposite_wire = second_wire->opposite_wire;
        second_wire->opposite_wire->opposite_wire = first_wire->opposite_wire;

        wire_destroy(&first_wire);
        wire_destroy(&second_wire);

        return;
    }

    case GET_FREE_WIRE_OP: {
        get_free_wire_op_t *op = (get_free_wire_op_t *) unknown_op;
        wire_t *free_wire = frame_get_free_wire(frame, op->node_spec, op->index);
        assert(free_wire);
        stack_push(worker->value_stack, free_wire);
        return;
    }
    }
}

void
node_apply_input_ports(node_t *node, worker_t *worker) {
    for (port_index_t c = 0; c < node->spec->input_arity; c++) {
        wire_t *wire = stack_pop(worker->value_stack);
        port_index_t i = node->spec->input_arity - 1 - c;
        wire->node = node;
        wire->index = i;
        node->wires[i] = wire;
    }
}

void
node_return_output_ports(node_t *node, worker_t *worker) {
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
