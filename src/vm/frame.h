#pragma once

frame_t *frame_new(const function_t *function);
void frame_destroy(frame_t **self_pointer);

void frame_collect_free_wires(frame_t *self, wire_t *wire);
wire_t *frame_use_free_wire(frame_t *self, const node_def_t *node_def, port_index_t index);

bool frame_is_finished(const frame_t *self);
op_t *frame_fetch_op(frame_t *self);
void frame_print(const frame_t *self, file_t *file);

value_t frame_local_get(const frame_t *self, size_t index);
void frame_local_set(frame_t *self, size_t index, value_t value);
