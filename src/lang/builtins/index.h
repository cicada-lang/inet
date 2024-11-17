#pragma once

void import_builtins(mod_t *self);

void builtin_wire_connect(worker_t *worker, frame_t *frame);
void builtin_wire_print_net(worker_t *worker, frame_t *frame);
void builtin_worker_interact(worker_t *worker, frame_t *frame);
