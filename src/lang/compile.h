#pragma once

void check_name_not_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token);
void check_name_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token);
void check_name_defined_to_node_spec(
    const worker_t *worker,
    const char *name,
    const token_t *token);

program_t *compile(const worker_t *worker, list_t *token_list);
