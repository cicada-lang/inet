#pragma once

typedef enum {
    CALL_OP,
    LITERAL_OP,
    LOCAL_GET_OP,
    LOCAL_SET_OP,
} op_kind_t;

typedef struct mod_t mod_t;
typedef struct function_t function_t;
typedef struct frame_t frame_t;
typedef struct vm_t vm_t;
typedef struct rule_t rule_t;

typedef struct primitive_def_t primitive_def_t;
typedef struct function_def_t function_def_t;
typedef struct constant_def_t constant_def_t;
typedef struct def_t def_t;

typedef struct op_t op_t;
typedef struct call_op_t call_op_t;
typedef struct literal_op_t literal_op_t;
typedef struct local_get_op_t local_get_op_t;
typedef struct local_set_op_t local_set_op_t;
typedef struct connect_op_t connect_op_t;
typedef struct use_free_wire_op_t use_free_wire_op_t;
