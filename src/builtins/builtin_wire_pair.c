#include "index.h"

void
builtin_wire_pair(worker_t *worker) {
    wire_t *first_wire = wire_new();
    wire_t *second_wire = wire_new();

    first_wire->opposite = second_wire;
    second_wire->opposite = first_wire;

    stack_push(worker->value_stack, first_wire);
    stack_push(worker->value_stack, second_wire);
}
