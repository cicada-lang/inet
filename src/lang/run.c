#include "index.h"

void
run_net(vm_t *vm) {
    while (!list_is_empty(vm->active_wire_list)) {
        step_net(vm);
    }
}

void
step_net(vm_t *vm) {
    wire_t *active_wire = list_pop(vm->active_wire_list);
    if (!active_wire) return;

    const rule_t *rule = mod_find_rule(
        vm->mod,
        active_wire,
        active_wire->opposite);
    if (!rule) return;

    size_t base_length = stack_length(vm->return_stack);
    frame_t *frame = frame_new(rule->function);
    frame_collect_free_wires(frame, active_wire);
    stack_push(vm->return_stack, frame);
    run_vm_until_until(vm, base_length);
}

void
run_vm_until_until(vm_t *vm, size_t base_length) {
    if (vm->log_level > 0) {
        vm_print(vm, stdout);
        fprintf(stdout, "\n");
    }

    while (stack_length(vm->return_stack) > base_length) {
        step_vm(vm);

        if (vm->log_level > 0) {
            vm_print(vm, stdout);
            fprintf(stdout, "\n");
        }
    }
}

void
step_vm(vm_t *vm) {
    if (stack_is_empty(vm->return_stack)) return;

    frame_t *frame = stack_pop(vm->return_stack);
    if (frame_is_finished(frame)) return;

    op_t *op = frame_fetch_op(frame);
    // proper tail-call = do not push finished frame.
    bool finished = frame_is_finished(frame);
    if (!finished) stack_push(vm->return_stack, frame);
    execute_operation(vm, frame, op);
    if (finished) frame_destroy(&frame);
}
