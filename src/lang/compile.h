#pragma once

void check_name_not_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token);
void check_spec_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token);
void check_node_spec_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token);

program_t *compile(const worker_t *worker, list_t *token_list);
