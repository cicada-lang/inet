#include "../index.h"

void
builtin_worker_print(worker_t *worker, frame_t *frame) {
    (void) frame;

    worker_print(worker);
    printf("\n");
}
