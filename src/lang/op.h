#pragma once

struct op_t { op_tag_t tag; };

struct op_call_program_t {
    op_tag_t tag;
    const program_spec_t *program_spec;
};

struct op_call_node_t {
    op_tag_t tag;
    const node_spec_t *node_spec;
};

struct op_connect_t {
    op_tag_t tag;
};

struct op_get_free_port_t {
    op_tag_t tag;
    const node_spec_t *node_spec;
    port_index_t index;
};

op_call_program_t *op_call_program_new(const program_spec_t *program_spec);
op_call_node_t *op_call_node_new(const node_spec_t *node_spec);
op_connect_t *op_connect_new(void);
op_get_free_port_t *op_get_free_port_new(const node_spec_t *node_spec, port_index_t index);

void op_call_program_destroy(op_call_program_t **self_pointer);
void op_call_node_destroy(op_call_node_t **self_pointer);
void op_connect_destroy(op_connect_t **self_pointer);
void op_get_free_port_destroy(op_get_free_port_t **self_pointer);

void op_destroy(op_t **self_pointer);
