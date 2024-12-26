#pragma once

typedef int8_t port_index_t;

typedef enum {
    PROGRAM_DEF_KIND,
    NODE_DEF_KIND,
    PRIMITIVE_DEF_KIND,
} def_kind_t;

typedef enum {
    CALL_OP_KIND,
    CONNECT_OP_KIND,
    GET_FREE_WIRE_OP_KIND,
} op_kind_t;

typedef struct node_t node_t;
typedef struct node_iter_t node_iter_t;
typedef struct wire_t wire_t;
typedef struct wire_iter_t wire_iter_t;
typedef struct mod_t mod_t;
typedef struct frame_t frame_t;
typedef struct vm_t vm_t;
typedef struct op_t op_t;
typedef struct call_op_t call_op_t;
typedef struct connect_op_t connect_op_t;
typedef struct use_free_wire_op_t use_free_wire_op_t;
typedef struct program_t program_t;
typedef struct rule_t rule_t;
typedef struct def_t def_t;
typedef struct node_def_t node_def_t;
typedef struct port_def_t port_def_t;
typedef struct primitive_def_t primitive_def_t;
typedef struct program_def_t program_def_t;
