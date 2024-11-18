#include "index.h"

void
builtin_swap(worker_t *worker) {
    wire_t *second = stack_pop(worker->value_stack);
    wire_t *first = stack_pop(worker->value_stack);

    stack_push(worker->value_stack, second);
    stack_push(worker->value_stack, first);
}
