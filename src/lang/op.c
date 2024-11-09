#include "index.h"

struct op_t { op_tag_t tag; };

struct op_exe_t { op_tag_t tag; program_spec_t *program_spec; };
struct op_app_t { op_tag_t tag; node_spec_t *node_spec; };
struct op_con_t { op_tag_t tag; };
struct op_fpt_t { op_tag_t tag; node_spec_t *node_spec; port_index_t port_index; };
