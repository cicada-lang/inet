#include "index.h"

void
builtin_debug(worker_t *worker) {
    fprintf(worker->out, "[debug] debug start\n");
    debug_start(worker);
    fprintf(worker->out, "[debug] debug end\n");
    fprintf(worker->out, "\n");    
}
