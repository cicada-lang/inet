#include "index.h"

struct op_t { const op_tag_t tag; };
struct op_exe_t { const op_tag_t tag; const program_definition_t *program_definition; };
struct op_app_t { const op_tag_t tag; const node_definition_t *node_definition; };
struct op_con_t { const op_tag_t tag; };
struct op_fpt_t { const op_tag_t tag; const port_index_t index; };
