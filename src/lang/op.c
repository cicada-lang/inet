#include "index.h"

struct op_t { op_tag_t tag; };
struct op_exe_t { op_tag_t tag; };
struct op_app_t { op_tag_t tag; node_definition_t *node_definition; };
struct op_con_t { op_tag_t tag; };
struct op_fpt_t { op_tag_t tag; port_index_t index; };
