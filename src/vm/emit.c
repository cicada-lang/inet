#include "index.h"

void
emit_call(const mod_t *mod, program_t *program, const char *name) {
    const spec_t *unknown_spec = mod_find_spec(mod, name);

    assert(unknown_spec && "[emit_call] unknown name");

    switch (unknown_spec->tag) {
    case BUILTIN_SPEC: {
        const builtin_spec_t *spec = (builtin_spec_t *) unknown_spec;
        program_add_op(program, (op_t *) call_builtin_op_new(spec));
        return;
    }

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

void
emit_connect(const mod_t *mod, program_t *program) {
    (void) mod;
    program_add_op(program, (op_t *) connect_op_new());
}

void
emit_use_free_wire(
    const mod_t *mod,
    program_t *program,
    const char *node_name,
    const char *port_name
) {
    const node_spec_t *node_spec = node_spec_cast(mod_find_spec(mod, node_name));
    port_index_t index = node_spec_find_port_index(node_spec, port_name);
    program_add_op(program, (op_t *) use_free_wire_op_new(node_spec, index));
}

void
emit_reconnect_free_wire(
    const mod_t *mod,
    program_t *program,
    const char *node_name,
    const char *port_name
) {
    emit_use_free_wire(mod, program, node_name, port_name);
    emit_connect(mod, program);
}
