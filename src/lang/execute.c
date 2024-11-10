#include "index.h"

void
execute(op_t *op, worker_t *self, frame_t *frame) {
    (void)self;
    (void)frame;
    switch (op->tag) {
    case OP_CALL_PROGRAM: {
        op_call_program_t *op = op;
        return;
    }

    case OP_CALL_NODE: {
        return;
    }

    case OP_CONNECT: {
        return;
    }

    case OP_GET_FREE_PORT: {
        return;
    }
    }
}
