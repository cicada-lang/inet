#include "index.h"

typedef enum {
    OP_EXECUTE_PROGRAM,
    OP_EXECUTE_NODE,
    OP_CONNECT,
    OP_GET_FREE_PORT,
} op_tag_t;

struct op_t {
    op_tag_t *tag;
};

typedef struct { op_tag_t *tag; } op_execute_program_t;
typedef struct { op_tag_t *tag; node_definition_t *node_definition; } op_execute_node_t;
typedef struct { op_tag_t *tag; } op_connect_t;
typedef struct { op_tag_t *tag; port_index_t index; } op_get_free_port_t;
