#include "../index.h"

void
builtin_worker_print_value_stack(worker_t *worker, frame_t *frame) {
    (void) frame;

    worker_print_value_stack(worker);
    printf("\n");
}
