#include "index.h"

vm_t *
vm_new(mod_t *mod) {
    vm_t *self = new(vm_t);
    self->mod = mod;
    self->active_wire_list = list_new();
    self->value_stack = stack_new_with((destroy_fn_t *) wire_destroy);
    self->return_stack = stack_new_with((destroy_fn_t *) frame_destroy);
    self->node_id_count = 0;
    self->log_level = 0;
    self->out = stdout;
    self->err = stderr;
    return self;
}

void
vm_destroy(vm_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        vm_t *self = *self_pointer;
        list_destroy(&self->active_wire_list);
        stack_destroy(&self->value_stack);
        stack_destroy(&self->return_stack);
        free(self);
        *self_pointer = NULL;
    }
}

void
run_net(vm_t *self) {
    while (!list_is_empty(self->active_wire_list)) {
        vm_net_step(self);
    }
}

void
vm_net_step(vm_t *self) {
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
    execute(self, frame, op);
    if (finished) frame_destroy(&frame);
}

void
vm_print(const vm_t *self, file_t *file) {
    fprintf(file, "<vm>\n");

    size_t active_wire_list_length = list_length(self->active_wire_list);
    fprintf(file, "<active-wire-list length=\"%lu\">\n", active_wire_list_length);
    wire_t *active_wire = list_first(self->active_wire_list);
    while (active_wire) {
        wire_print(active_wire, file);
        fprintf(file, "\n");
        active_wire = list_next(self->active_wire_list);
    }
    fprintf(file, "</active-wire-list>\n");

    vm_print_return_stack(self, file);
    vm_print_value_stack(self, file);

    fprintf(file, "</vm>\n");
}

void
vm_print_return_stack(const vm_t *self, file_t *file) {
    size_t return_stack_length = stack_length(self->return_stack);
    fprintf(file, "<return-stack length=\"%lu\">\n", return_stack_length);
    for (size_t i = 0; i < return_stack_length; i++) {
        frame_t *frame = stack_get(self->return_stack, i);
        frame_print(frame, file);
    }

    fprintf(file, "</return-stack>\n");
}

void
vm_print_value_stack(const vm_t *self, file_t *file) {
    size_t value_stack_length = stack_length(self->value_stack);
    fprintf(file, "<value-stack length=\"%lu\">\n", value_stack_length);
    for (size_t i = 0; i < value_stack_length; i++) {
        wire_t *wire = stack_get(self->value_stack, i);
        wire_print(wire, file);
        fprintf(file, "\n");
    }

    fprintf(file, "</value-stack>\n");
}

void
vm_connect_top_wire_pair(vm_t *vm) {
    wire_t *second_wire = stack_pop(vm->value_stack);
    wire_t *first_wire = stack_pop(vm->value_stack);

    wire_t *first_opposite = wire_connect(second_wire, first_wire);

    vm_maybe_add_active_wire(
        vm,
        first_opposite,
        first_opposite->opposite);
}

void
vm_maybe_add_active_wire(
    vm_t *vm,
    wire_t *first_wire,
    wire_t *second_wire
) {
    if (wire_is_principal(first_wire) && wire_is_principal(second_wire)) {
        assert(first_wire->opposite == second_wire);
        assert(second_wire->opposite == first_wire);

        list_push(vm->active_wire_list, first_wire);
    }
}
