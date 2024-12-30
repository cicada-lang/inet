#include "index.h"

void
execute_operation(vm_t *vm, frame_t *frame, op_t *unknown_op) {
    switch (unknown_op->kind) {
    case CALL_OP: {
        call_op_t *op = (call_op_t *) unknown_op;
        call(vm, op->def);
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
