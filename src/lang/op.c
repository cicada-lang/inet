#include "index.h"

struct op_t { const op_tag_t tag; };

struct op_exe_t {
    const op_tag_t tag;
    const program_spec_t *program_spec;
};

struct op_app_t {
    const op_tag_t tag;
    const node_spec_t *node_spec;
};

struct op_con_t {
    const op_tag_t tag;
};

struct op_fpt_t {
    const op_tag_t tag;
    const node_spec_t *node_spec;
    const port_index_t port_index;
};
