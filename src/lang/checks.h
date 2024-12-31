#pragma once

void check_name_not_defined(
    const vm_t *vm,
    const char *name,
    const token_t *token);
void check_name_defined(
    const vm_t *vm,
    const char *name,
    const token_t *token);
void check_node_name_defined(
    const vm_t *vm,
    const char *name,
    const token_t *token);
void check_port_name_defined(
    const vm_t *vm,
    const char *node_name,
    const char *port_name,
    const token_t *token);
