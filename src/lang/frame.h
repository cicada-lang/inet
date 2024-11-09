#pragma once

frame_t *frame_new(const program_t *program);
void frame_destroy(frame_t **self_pointer);

void frame_set_active_edge(frame_t *self, edge_t *active_edge);
// port_t *frame_get_free_port(frame_t *self, const node_spec_t *node_spec, port_index_t index);
