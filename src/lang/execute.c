#include "index.h"

static void node_apply_input_ports(worker_t *worker, node_t *node);
static void node_return_output_ports(worker_t *worker, node_t *node);
static void maybe_add_active_pair(worker_t *worker, wire_t *first_wire, wire_t *second_wire);

void
execute(worker_t *worker, frame_t *frame, op_t *unknown_op) {
    switch (unknown_op->tag) {
    case CALL_BUILTIN_OP: {
        assert(false);
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
        node_t *node = node_new(op->node_spec);
        node_apply_input_ports(worker, node);
        node_return_output_ports(worker, node);
        return;
    }

    case CONNECT_OP: {
        wire_t *second_wire = stack_pop(worker->value_stack);
        wire_t *first_wire = stack_pop(worker->value_stack);

        wire_t *first_opposite_wire = first_wire->opposite_wire;
        wire_t *second_opposite_wire = second_wire->opposite_wire;

        first_opposite_wire->opposite_wire = second_opposite_wire;
        second_opposite_wire->opposite_wire = first_opposite_wire;

        maybe_add_active_pair(worker, first_opposite_wire, second_opposite_wire);

        wire_destroy(&first_wire);
        wire_destroy(&second_wire);

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

        maybe_add_active_pair(worker, wire, wire->opposite_wire);
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

void maybe_add_active_pair(
    worker_t *worker,
    wire_t *first_wire,
    wire_t *second_wire
) {
    if (wire_is_principal(first_wire) && wire_is_principal(second_wire)) {
        assert(first_wire->opposite_wire == second_wire);
        assert(second_wire->opposite_wire == first_wire);

        active_pair_t *active_pair = active_pair_new(first_wire, second_wire);
        list_push(worker->active_pair_list, active_pair);
    }
}
