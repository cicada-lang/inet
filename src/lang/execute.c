#include "index.h"

void
execute(op_t *op, worker_t *worker, frame_t *frame) {
    (void)worker;
    (void)frame;
    switch (op->tag) {
    case OP_CALL_PROGRAM: {
        op_call_program_t *op = op;
        frame_t *frame = frame_new(op->program_spec->program);
        stack_push(worker->frame_stack, frame);
        return;
    }

    case OP_CALL_NODE: {
        op_call_node_t *op = op;
        return;
    }

    case OP_CONNECT: {
        op_connect_t *op = op;
        return;
    }

    case OP_GET_FREE_PORT: {
        op_get_free_port_t *op = op;
        return;
    }
    }
}
