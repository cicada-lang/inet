#pragma once

typedef uint8_t byte_t;
typedef int32_t node_id_t;
typedef int32_t port_index_t;

typedef enum { POSITIVE_SIGN, NEGATIVE_SIGN } sign_t;
typedef enum { PROGRAM_SPEC, NODE_SPEC } spec_tag_t;
typedef enum {
    CALL_PROGRAM_OP,
    CALL_NODE_OP,
    CONNECT_OP,
    GET_FREE_PORT_OP,
} op_tag_t;

typedef struct node_t node_t;
typedef struct port_t port_t;
typedef struct active_pair_t active_pair_t;
typedef struct mod_t mod_t;
typedef struct frame_t frame_t;
typedef struct worker_t worker_t;
typedef struct op_t op_t;
typedef struct call_program_op_t call_program_op_t;
typedef struct call_node_op_t call_node_op_t;
typedef struct connect_op_t connect_op_t;
typedef struct get_free_port_op_t get_free_port_op_t;
typedef struct program_t program_t;
typedef struct rule_t rule_t;
typedef struct spec_t spec_t;
typedef struct node_spec_t node_spec_t;
typedef struct port_spec_t port_spec_t;
typedef struct program_spec_t program_spec_t;
