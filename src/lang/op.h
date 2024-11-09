#pragma once

op_exe_t *op_exe_new(const program_spec_t *program_spec);
op_app_t *op_app_new(const node_spec_t *node_spec);
op_con_t *op_con_new(void);
op_fpt_t *op_fpt_new(const node_spec_t *node_spec, port_index_t index);
