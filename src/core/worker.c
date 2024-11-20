#include "index.h"

worker_t *
worker_new(mod_t *mod) {
    worker_t *self = allocate(sizeof(worker_t));
    self->mod = mod;

    self->active_wire_list = list_new();

    self->value_stack = stack_new(VALUE_STACK_SIZE);
    stack_set_item_destructor(
        self->value_stack,
        (stack_item_destructor_t *) wire_destroy);

    self->return_stack = stack_new(RETURN_STACK_SIZE);
    stack_set_item_destructor(
        self->return_stack,
        (stack_item_destructor_t *) frame_destroy);

    self->node_id_count = 0;
    self->debug = false;
    self->out = stdout;
    self->err = stderr;

    return self;
}

void
worker_destroy(worker_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        worker_t *self = *self_pointer;
        list_destroy(&self->active_wire_list);
        stack_destroy(&self->value_stack);
        stack_destroy(&self->return_stack);
        free(self);
        *self_pointer = NULL;
    }
}

void
worker_interact(worker_t *self) {
    while (!list_is_empty(self->active_wire_list)) {
        worker_interact_once(self);
    }
}

void
worker_interact_once(worker_t *self) {
    wire_t *active_wire = list_pop(self->active_wire_list);
    if (!active_wire) return;

    const rule_t *rule = mod_find_rule(
        self->mod,
        active_wire,
        active_wire->opposite_wire);
    if (!rule) return;

    size_t base_length = stack_length(self->return_stack);
    frame_t *frame = frame_new(rule->program);
    frame_collect_free_wires(frame, active_wire);
    stack_push(self->return_stack, frame);
    worker_run_until(self, base_length);
}

void
worker_run_until(worker_t *self, size_t base_length) {
    if (self->debug) {
        worker_print(self, self->out);
        fprintf(self->out, "\n");
    }

    while (stack_length(self->return_stack) > base_length) {
        worker_step(self);

        if (self->debug) {
            worker_print(self, self->out);
            fprintf(self->out, "\n");
        }
    }
}

void
worker_step(worker_t *self) {
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
worker_print(const worker_t *self, file_t *file) {
    fprintf(file, "<worker>\n");

    mod_print(self->mod, file);

    size_t active_wire_list_length = list_length(self->active_wire_list);
    fprintf(file, "<active-wire-list length=\"%lu\">\n", active_wire_list_length);
    wire_t *active_wire = list_start(self->active_wire_list);
    while (active_wire) {
        wire_print(active_wire, file);
        fprintf(file, "\n");
        active_wire = list_next(self->active_wire_list);
    }
    fprintf(file, "</active-wire-list>\n");

    worker_print_return_stack(self, file);
    worker_print_value_stack(self, file);

    fprintf(file, "</worker>\n");
}

void
worker_print_return_stack(const worker_t *self, file_t *file) {
    size_t return_stack_length = stack_length(self->return_stack);
    fprintf(file, "<return-stack length=\"%lu\">\n", return_stack_length);
    for (size_t i = 0; i < return_stack_length; i++) {
        frame_t *frame = stack_get(self->return_stack, i);
        frame_print(frame, file);
    }

    fprintf(file, "</return-stack>\n");
}

void
worker_print_value_stack(const worker_t *self, file_t *file) {
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
worker_connect_top_wire_pair(worker_t *worker) {
    wire_t *second_wire = stack_pop(worker->value_stack);
    wire_t *first_wire = stack_pop(worker->value_stack);

    wire_t *first_opposite_wire = wire_connect(second_wire, first_wire);

    worker_maybe_add_active_wire(
        worker,
        first_opposite_wire,
        first_opposite_wire->opposite_wire);
}

void
worker_maybe_add_active_wire(
    worker_t *worker,
    wire_t *first_wire,
    wire_t *second_wire
) {
    if (wire_is_principal(first_wire) && wire_is_principal(second_wire)) {
        assert(first_wire->opposite_wire == second_wire);
        assert(second_wire->opposite_wire == first_wire);

        list_push(worker->active_wire_list, first_wire);
    }
}
