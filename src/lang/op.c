#include "index.h"

struct op_t { op_tag_t tag; };

struct op_exe_t { op_tag_t tag; const program_spec_t *program_spec; };
struct op_app_t { op_tag_t tag; const node_spec_t *node_spec; };
struct op_con_t { op_tag_t tag; };
struct op_fpt_t { op_tag_t tag; const node_spec_t *node_spec; port_index_t index; };

op_exe_t *
op_exe_new(const program_spec_t *program_spec) {
    op_exe_t *self = allocate(sizeof(op_exe_t));
    self->tag = OP_EXE;    
    self->program_spec = program_spec;
    return self;
}
