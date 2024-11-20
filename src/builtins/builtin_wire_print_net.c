#include "index.h"

void
builtin_wire_print_net(worker_t *worker) {
    wire_t *wire = stack_top(worker->value_stack);
    wire_print_net(wire, worker->out);
    fprintf(worker->out, "\n");
}
