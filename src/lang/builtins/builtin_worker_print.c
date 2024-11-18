#include "../index.h"

void
builtin_worker_print(worker_t *worker) {
    worker_print(worker);
    printf("\n");
}
