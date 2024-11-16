#include "index.h"

void
builtin_inspect(worker_t *worker, frame_t *frame) {
    (void) frame;

    wire_t *wire = stack_pop(worker->value_stack);
    wire_inspect(wire);
    stack_push(worker->value_stack, wire);
}
