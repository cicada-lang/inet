#include "index.h"

typedef enum {
    OP_EXE,
    OP_APP,
    OP_CON,
    OP_FPT,
} op_tag_t;

struct op_t {
    op_tag_t *tag;
};

typedef struct { op_tag_t *tag; } op_exe_t;
typedef struct { op_tag_t *tag; node_definition_t *node_definition; } op_app_t;
typedef struct { op_tag_t *tag; } op_con_t;
typedef struct { op_tag_t *tag; port_index_t index; } op_fpt_t;
