#include "index.h"

void
emit_call(const mod_t *mod, program_t *program, const char *name) {
    const spec_t *unknown_spec = mod_find_spec(mod, name);
    switch (unknown_spec->tag) {
    case PROGRAM_SPEC: {
        const program_spec_t *spec = (program_spec_t *) unknown_spec;
        program_add_op(program, (op_t *) call_program_op_new(spec));
        return;
    }

    case NODE_SPEC: {
        const node_spec_t *spec = (node_spec_t *) unknown_spec;
        program_add_op(program, (op_t *) call_node_op_new(spec));
        return;
    }
    }
}
