#include "index.h"

void
builtin_wire_connect(worker_t *worker) {
    wire_t *second_wire = stack_pop(worker->value_stack);
    wire_t *first_wire = stack_pop(worker->value_stack);

    wire_t *first_opposite_wire = wire_connect(second_wire, first_wire);

    worker_maybe_add_active_wire(
        worker,
        first_opposite_wire,
        first_opposite_wire->opposite_wire);
}
