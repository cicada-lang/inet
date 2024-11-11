#include "index.h"

static void node_apply_input_ports(node_t *node, worker_t *worker);
static void node_return_output_ports(node_t *node, worker_t *worker);

void
execute(op_t *op_unknown, worker_t *worker, frame_t *frame) {
    switch (op_unknown->tag) {
    case OP_CALL_PROGRAM: {
        op_call_program_t *op = (op_call_program_t *) op_unknown;
        frame_t *frame = frame_new(op->program_spec->program);
        stack_push(worker->frame_stack, frame);
        return;
    }

    case OP_CALL_NODE: {
        op_call_node_t *op = (op_call_node_t *) op_unknown;
        node_t *node = node_new(op->node_spec);
        node_apply_input_ports(node, worker);
        node_return_output_ports(node, worker);
        return;
    }

    case OP_CONNECT: {
        port_t *second_port = stack_pop(worker->port_stack);
        port_t *first_port = stack_pop(worker->port_stack);

        first_port->opposite_port->opposite_port = second_port->opposite_port;
        second_port->opposite_port->opposite_port = first_port->opposite_port;

        port_destroy(&first_port);
        port_destroy(&second_port);

        return;
    }

    case OP_GET_FREE_PORT: {
        op_get_free_port_t *op = (op_get_free_port_t *) op_unknown;
        port_t *free_port = frame_get_free_port(frame, op->node_spec, op->index);
        assert(free_port);
        stack_push(worker->port_stack, free_port);
        return;
    }
    }
}

void
node_apply_input_ports(node_t *node, worker_t *worker) {
    for (size_t c = 0; c < node->spec->input_arity; c++) {
        port_t *port = stack_pop(worker->port_stack);
        size_t i = node->spec->input_arity - 1 - c;
        port->node = node;
        port->index = i;
        node->ports[i] = port;
    }
}

void
node_return_output_ports(node_t *node, worker_t *worker) {
    for (size_t c = 0; c < node->spec->output_arity; c++) {
        port_t *node_port = port_new();
        port_t *free_port = port_new();

        node_port->opposite_port = free_port;
        free_port->opposite_port = node_port;

        size_t i = node->spec->output_arity + c;
        node_port->node = node;
        node_port->index = i;
        node->ports[i] = node_port;

        stack_push(worker->port_stack, free_port);
    }
}
