#pragma once

struct op_t { op_tag_t tag; };

struct op_exe_t { op_tag_t tag; const program_spec_t *program_spec; };
struct op_app_t { op_tag_t tag; const node_spec_t *node_spec; };
struct op_con_t { op_tag_t tag; };
struct op_fpt_t { op_tag_t tag; const node_spec_t *node_spec; port_index_t index; };

op_exe_t *op_exe_new(const program_spec_t *program_spec);
op_app_t *op_app_new(const node_spec_t *node_spec);
op_con_t *op_con_new(void);
op_fpt_t *op_fpt_new(const node_spec_t *node_spec, port_index_t index);

void op_exe_destroy(op_exe_t **self_pointer);
void op_app_destroy(op_app_t **self_pointer);
void op_con_destroy(op_con_t **self_pointer);
void op_fpt_destroy(op_fpt_t **self_pointer);

void op_destroy(op_t **self_pointer);
