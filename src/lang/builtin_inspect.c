#include "index.h"

void
builtin_inspect(worker_t *worker, frame_t *frame) {
    (void) frame;

    wire_t *wire = stack_top(worker->value_stack);
    wire_inspect(wire);
}
