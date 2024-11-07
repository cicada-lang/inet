#pragma once

typedef uint8_t byte_t;
typedef int32_t node_id_t;
typedef int32_t port_index_t;

typedef enum { POSITIVE_SIGN, NEGATIVE_SIGN } sign_t;
typedef enum { OP_EXE, OP_APP, OP_CON, OP_FPT } op_tag_t;
typedef enum { PROGRAM_DEFINITION, NODE_DEFINITION } definition_tag_t;

typedef struct node_t node_t;
typedef struct port_t port_t;
typedef struct edge_t edge_t;
typedef struct mod_t mod_t;
typedef struct worker_t worker_t;
typedef struct op_t op_t;
typedef struct op_exe_t op_exe_t;
typedef struct op_app_t op_app_t;
typedef struct op_con_t op_con_t;
typedef struct op_fpt_t op_fpt_t;
typedef struct program_t program_t;
typedef struct definition_t definition_t;
typedef struct node_definition_t node_definition_t;
typedef struct port_definition_t port_definition_t;
typedef struct program_definition_t program_definition_t;
