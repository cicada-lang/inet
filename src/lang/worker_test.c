#include "index.h"

void
worker_test(void) {
    printf("<worker_test>\n");

    mod_t *mod = mod_new();
    mod_import_nat(mod);

    worker_t *worker = worker_new(mod);

    program_t *program = program_new();
    emit_call(mod, program, "zero");
    emit_call(mod, program, "zero");
    emit_call(mod, program, "add1");
    emit_call(mod, program, "add");
    program_build(program);

    frame_t *frame = frame_new(program);
    stack_push(worker->return_stack, frame);

    worker->debug = true;
    worker_run(worker);
    worker_interact(worker);

    worker_destroy(&worker);
    mod_destroy(&mod);

    printf("</worker_test>\n");
}
