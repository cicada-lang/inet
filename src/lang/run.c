#include "index.h"

void
run_net(vm_t *self) {
    while (!list_is_empty(self->active_wire_list)) {
        step_net(self);
    }
}

void
step_net(vm_t *self) {
    wire_t *active_wire = list_pop(self->active_wire_list);
    if (!active_wire) return;

    const rule_t *rule = mod_find_rule(
        self->mod,
        active_wire,
        active_wire->opposite);
    if (!rule) return;

    size_t base_length = stack_length(self->return_stack);
    frame_t *frame = frame_new(rule->function);
    frame_collect_free_wires(frame, active_wire);
    stack_push(self->return_stack, frame);
    run_vm_until_until(self, base_length);
}

void
run_vm_until_until(vm_t *self, size_t base_length) {
    if (self->log_level > 0) {
        vm_print(self, self->out);
        fprintf(self->out, "\n");
    }

    while (stack_length(self->return_stack) > base_length) {
        step_vm(self);

        if (self->log_level > 0) {
            vm_print(self, self->out);
            fprintf(self->out, "\n");
        }
    }
}

void
step_vm(vm_t *self) {
    if (stack_is_empty(self->return_stack)) return;

    frame_t *frame = stack_pop(self->return_stack);
    if (frame_is_finished(frame)) return;

    op_t *op = frame_fetch_op(frame);
    // proper tail-call = do not push finished frame.
    bool finished = frame_is_finished(frame);
    if (!finished) stack_push(self->return_stack, frame);
    execute_operation(self, frame, op);
    if (finished) frame_destroy(&frame);
}
