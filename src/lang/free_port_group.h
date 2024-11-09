#pragma once

free_port_group_t *free_port_group_new(const node_spec_t *node_spec);
void free_port_group_destroy(free_port_group_t **self_pointer);
