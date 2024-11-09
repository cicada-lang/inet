#pragma once

worker_t *worker_new(const mod_t *mod);
void worker_destroy(worker_t **self_pointer);
