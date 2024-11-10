#pragma once

frame_t *frame_new(const program_t *program);
void frame_destroy(frame_t **self_pointer);

void frame_collect_free_ports(frame_t *self, active_pair_t *active_pair);
port_t *frame_get_free_port(frame_t *self, const node_spec_t *node_spec, port_index_t index);

bool frame_is_finished(const frame_t *self);
const op_t *frame_fetch_op(frame_t *self);
