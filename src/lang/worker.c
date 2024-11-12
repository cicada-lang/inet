#include "index.h"

worker_t *
worker_new(const mod_t *mod) {
    worker_t *self = allocate(sizeof(worker_t));
    self->mod = mod;

    self->active_pair_list = list_new();
    list_set_item_destructor(
        self->active_pair_list,
        (list_item_destructor_t *) active_pair_destroy);

    self->value_stack = stack_new(VALUE_STACK_SIZE);
    stack_set_item_destructor(
        self->value_stack,
        (stack_item_destructor_t *) wire_destroy);

    self->return_stack = stack_new(RETURN_STACK_SIZE);
    stack_set_item_destructor(
        self->return_stack,
        (stack_item_destructor_t *) frame_destroy);

    self->debug = false;

    return self;
}

void
worker_destroy(worker_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        worker_t *self = *self_pointer;
        list_destroy(&self->active_pair_list);
        stack_destroy(&self->value_stack);
        stack_destroy(&self->return_stack);
        free(self);
        *self_pointer = NULL;
    }
}

void
worker_interact(worker_t *self) {
    active_pair_t *active_pair = list_pop(self->active_pair_list);
    if (active_pair) {
        const rule_t *rule = mod_find_rule(self->mod, active_pair);
        assert(rule);
        frame_t *frame = frame_new(rule->program);
        frame_collect_free_wires(frame, active_pair);
        stack_push(self->return_stack, frame);
        worker_run(self);
    }
}

void
worker_run(worker_t *self) {
    if (self->debug) {
        worker_print(self);
        printf("\n");
    }

    while (!stack_is_empty(self->return_stack)) {
        worker_step(self);

        if (self->debug) {
            worker_print(self);
            printf("\n");
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
    execute(op, self, frame);
    if (finished) frame_destroy(&frame);
}

void
worker_print(const worker_t *self) {
    printf("<worker>\n");

    mod_print(self->mod);

    size_t active_pair_list_length = list_length(self->active_pair_list);
    printf("<active_pair_list length=\"%lu\">\n", active_pair_list_length);
    active_pair_t *active_pair = list_start(self->active_pair_list);
    while (active_pair) {
        active_pair_print(active_pair);
        printf("\n");
        active_pair = list_next(self->active_pair_list);
    }
    printf("</active_pair_list>\n");

    size_t return_stack_length = stack_length(self->return_stack);
    printf("<return_stack length=\"%lu\">\n", return_stack_length);
    for (size_t i = 0; i < return_stack_length; i++) {
        frame_t *frame = stack_get(self->return_stack, i);
        frame_print(frame);
    }
    printf("</return_stack>\n");

    size_t value_stack_length = stack_length(self->value_stack);
    printf("<value_stack length=\"%lu\">\n", value_stack_length);
    for (size_t i = 0; i < value_stack_length; i++) {
        wire_t *wire = stack_get(self->value_stack, i);
        printf("- ");
        wire_print(wire);
        printf("\n");
    }
    printf("</value_stack>\n");

    printf("</worker>\n");
}
