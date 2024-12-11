#include "index.h"

void
builtin_print_worker(worker_t *worker) {
    worker_print(worker, worker->out);
    fprintf(worker->out, "\n");
}
