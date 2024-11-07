#pragma once

typedef uint8_t byte_t;
typedef int32_t node_id_t;
typedef int32_t port_index_t;

typedef enum { POSITIVE_SIGN, NEGATIVE_SIGN } sign_t;
typedef enum { OP_EXE, OP_APP, OP_CON, OP_FPT } op_tag_t;
typedef enum { PROGRAM_SPEC, NODE_SPEC } spec_tag_t;

typedef struct node_t node_t;
typedef struct port_t port_t;
typedef struct edge_t edge_t;
typedef struct mod_t mod_t;
typedef struct free_port_group_t free_port_group_t;
typedef struct frame_t frame_t;
typedef struct worker_t worker_t;
typedef struct op_t op_t;
typedef struct op_exe_t op_exe_t;
typedef struct op_app_t op_app_t;
typedef struct op_con_t op_con_t;
typedef struct op_fpt_t op_fpt_t;
typedef struct program_t program_t;
typedef struct rule_t rule_t;
typedef struct spec_t spec_t;
typedef struct node_spec_t node_spec_t;
typedef struct port_spec_t port_spec_t;
typedef struct program_spec_t program_spec_t;
