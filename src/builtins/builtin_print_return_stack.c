#include "index.h"

void
builtin_print_return_stack(worker_t *worker) {
    worker_print_return_stack(worker);
    printf("\n");
}
