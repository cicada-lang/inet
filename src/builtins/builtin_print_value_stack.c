#include "index.h"

void
builtin_print_value_stack(worker_t *worker) {
    worker_print_value_stack(worker);
    printf("\n");
}
