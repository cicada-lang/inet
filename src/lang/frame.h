#pragma once

frame_t *frame_new(const program_t *program);
void frame_destroy(frame_t **self_pointer);

void frame_collect_free_wires(frame_t *self, active_pair_t *active_pair);
wire_t *frame_get_free_wire(frame_t *self, const node_spec_t *node_spec, wire_index_t index);

bool frame_is_finished(const frame_t *self);
op_t *frame_fetch_op(frame_t *self);
void frame_print(const frame_t *self);
