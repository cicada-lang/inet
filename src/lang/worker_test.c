#include "index.h"

void
worker_test(void) {
    printf("<worker_test>\n");

    mod_t *mod = mod_new();

    node_spec_t *zero_spec = node_spec_new("zero", 0, 1);
    zero_spec->port_specs[0] = port_spec_new("value", true);
    mod_define(mod, (spec_t *) zero_spec);

    node_spec_t *add1_spec = node_spec_new("add1", 1, 1);
    add1_spec->port_specs[0] = port_spec_new("prev", false);
    add1_spec->port_specs[1] = port_spec_new("value", true);
    mod_define(mod, (spec_t *) add1_spec);

    node_spec_t *add_spec = node_spec_new("add", 2, 1);
    add_spec->port_specs[0] = port_spec_new("target", true);
    add_spec->port_specs[1] = port_spec_new("addend", false);
    add_spec->port_specs[2] = port_spec_new("value", false);
    mod_define(mod, (spec_t *) add_spec);

    worker_t *worker = worker_new(mod);

    program_t *program = program_new();
    program_add_op(program, (op_t *) call_node_op_new(zero_spec));
    program_add_op(program, (op_t *) call_node_op_new(zero_spec));
    program_add_op(program, (op_t *) call_node_op_new(add1_spec));
    program_add_op(program, (op_t *) call_node_op_new(add_spec));
    program_build(program);

    frame_t *frame = frame_new(program);
    stack_push(worker->frame_stack, frame);

    worker_print(worker);
    worker_run(worker);
    worker_print(worker);
    assert(stack_length(worker->port_stack) == 1);

    worker_destroy(&worker);
    mod_destroy(&mod);

    printf("</worker_test>\n");
}
