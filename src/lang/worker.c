#include "index.h"

worker_t *
worker_new(const mod_t *mod) {
    worker_t *self = allocate(sizeof(worker_t));
    self->mod = mod;

    self->active_pair_list = list_new();
    list_set_item_destructor(
        self->active_pair_list,
        (list_item_destructor_t *) active_pair_destroy);

    self->port_stack = stack_new(10000);
    stack_set_item_destructor(
        self->port_stack,
        (stack_item_destructor_t *) port_destroy);

    self->frame_stack = stack_new(10000);
    stack_set_item_destructor(
        self->frame_stack,
        (stack_item_destructor_t *) frame_destroy);

    return self;
}

void
worker_destroy(worker_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        worker_t *self = *self_pointer;
        list_destroy(&self->active_pair_list);
        stack_destroy(&self->port_stack);
        stack_destroy(&self->frame_stack);
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
        frame_collect_free_ports(frame, active_pair);
        stack_push(self->frame_stack, frame);
        worker_run(self);
    }
}

void
worker_run(worker_t *self) {
    while (!stack_is_empty(self->frame_stack)) {
        frame_t *frame = stack_pop(self->frame_stack);
        worker_step(self, frame);
    }
}

void
worker_step(worker_t *self, frame_t *frame) {
    if (frame_is_finished(frame)) return;

    op_t *op = frame_fetch_op(frame);

    // proper tail-call = do not push finished frame.
    bool finished = frame_is_finished(frame);
    if (!finished) stack_push(self->frame_stack, frame);

    execute(op, self, frame);

    if (finished) frame_destroy(&frame);
}
