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
void check_port_name_defined(
    const worker_t *worker,
    const char *node_name,
    const char *port_name,
    const token_t *token);
