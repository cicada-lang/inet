#include "index.h"

worker_t *
worker_new(const mod_t *mod) {
    worker_t *self = allocate(sizeof(worker_t));
    self->mod = mod;

    self->active_pair_list = list_new();
    list_set_item_destructor(
        self->active_pair_list,
        (list_item_destructor_t *) active_pair_destroy);

    self->port_stack = stack_new(PORT_STACK_SIZE);
    stack_set_item_destructor(
        self->port_stack,
        (stack_item_destructor_t *) port_destroy);

    self->frame_stack = stack_new(FRAME_STACK_SIZE);
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
        worker_step(self);
    }
}

void
worker_step(worker_t *self) {
    if (stack_is_empty(self->frame_stack)) return;

    frame_t *frame = stack_pop(self->frame_stack);
    if (frame_is_finished(frame)) return;

    op_t *op = frame_fetch_op(frame);
    // proper tail-call = do not push finished frame.
    bool finished = frame_is_finished(frame);
    if (!finished) stack_push(self->frame_stack, frame);
    execute(op, self, frame);
    if (finished) frame_destroy(&frame);
}

void
worker_print(const worker_t *self) {
    printf("<worker>\n");

    mod_print(self->mod);

    size_t frame_stack_length = stack_length(self->frame_stack);
    printf("<frame_stack length=\"%lu\">\n", frame_stack_length);
    for (size_t i = 0; i < frame_stack_length; i++) {
        frame_t *frame = stack_get(self->frame_stack, i);
        frame_print(frame);
    }
    printf("</frame_stack>\n");

    size_t port_stack_length = stack_length(self->port_stack);
    printf("<port_stack length=\"%lu\">\n", port_stack_length);
    for (size_t i = 0; i < port_stack_length; i++) {
        port_t *port = stack_get(self->port_stack, i);
        printf("- ");
        port_print(port);
        printf("\n");
    }
    printf("</port_stack>\n");

    printf("</worker>\n");
}
