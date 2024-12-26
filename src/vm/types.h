#pragma once

typedef int8_t port_index_t;

typedef enum { POSITIVE_SIGN, NEGATIVE_SIGN } sign_t;
typedef enum {
    PROGRAM_DEF,
    NODE_DEF,
    BUILTIN_DEF,
} def_kind_t;

typedef enum {
    CALL_BUILTIN_OP,
    CALL_PROGRAM_OP,
    CALL_NODE_OP,
    CONNECT_OP,
    GET_FREE_WIRE_OP,
} op_kind_t;

typedef struct node_t node_t;
typedef struct node_iter_t node_iter_t;
typedef struct wire_t wire_t;
typedef struct wire_iter_t wire_iter_t;
typedef struct mod_t mod_t;
typedef struct frame_t frame_t;
typedef struct vm_t vm_t;
typedef struct op_t op_t;
typedef struct call_builtin_op_t call_builtin_op_t;
typedef struct call_program_op_t call_program_op_t;
typedef struct call_node_op_t call_node_op_t;
typedef struct connect_op_t connect_op_t;
typedef struct use_free_wire_op_t use_free_wire_op_t;
typedef struct program_t program_t;
typedef struct rule_t rule_t;
typedef struct def_t def_t;
typedef struct node_def_t node_def_t;
typedef struct port_def_t port_def_t;
typedef struct builtin_def_t builtin_def_t;
typedef struct program_def_t program_def_t;
