#include "index.h"

void
builtin_worker_interact(worker_t *worker, frame_t *frame) {
    (void) frame;

    worker_interact(worker);
}
