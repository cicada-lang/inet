#pragma once

worker_t *worker_new(const mod_t *mod);
void worker_destroy(worker_t **self_pointer);

void worker_interact(worker_t *self);
void worker_run(worker_t *self);
