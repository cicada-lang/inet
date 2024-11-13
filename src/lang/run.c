#include "index.h"

worker_t *
run_text(const char *text) {
    mod_t *mod = mod_new();
    worker_t *worker = worker_new(mod);
    worker->debug = true;
    interpret_text(worker, text);
    return worker;
}
