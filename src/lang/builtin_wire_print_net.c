#include "index.h"

void
builtin_wire_print_net(worker_t *worker, frame_t *frame) {
    (void) frame;

    wire_t *wire = stack_top(worker->value_stack);
    wire_print_net(wire);
}
