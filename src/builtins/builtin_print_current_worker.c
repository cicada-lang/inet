#include "index.h"

void
builtin_print_current_worker(worker_t *worker) {
    worker_print(worker);
    printf("\n");
}
