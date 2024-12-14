#include "index.h"

void
builtin_connect(worker_t *worker) {
    worker_connect_top_wire_pair(worker);
}
