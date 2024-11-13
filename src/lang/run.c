#include "index.h"

worker_t *
run_text(const char *text) {
    mod_t *mod = mod_new();
    worker_t *worker = worker_new(mod);

    worker->debug = true;

    list_t *stmt_list = parse(text);
    stmt_t *stmt = list_start(stmt_list);
    while (stmt) {
        interpret_stmt(worker, stmt);
        stmt = list_next(stmt_list);
    }

    return worker;
}
