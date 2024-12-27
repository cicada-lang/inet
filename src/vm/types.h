#pragma once

typedef enum {
    CALL_OP,
    CONNECT_OP,
    GET_FREE_WIRE_OP,
} op_kind_t;

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
typedef struct primitive_def_t primitive_def_t;
typedef struct program_def_t program_def_t;
