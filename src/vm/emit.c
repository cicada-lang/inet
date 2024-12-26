#include "index.h"

void
emit_call(const mod_t *mod, program_t *program, const char *name) {
    const def_t *unknown_def = mod_find_def(mod, name);

    assert(unknown_def && "[emit_call] unknown name");

    switch (unknown_def->kind) {
    case PRIMITIVE_DEF: {
        const primitive_def_t *def = (primitive_def_t *) unknown_def;
        program_add_op(program, (op_t *) call_primitive_op_new(def));
        return;
    }

    case PROGRAM_DEF: {
        const program_def_t *def = (program_def_t *) unknown_def;
        program_add_op(program, (op_t *) call_program_op_new(def));
        return;
    }

    case NODE_DEF: {
        const node_def_t *def = (node_def_t *) unknown_def;
        program_add_op(program, (op_t *) call_node_op_new(def));
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
    const node_def_t *node_def = node_def_cast(mod_find_def(mod, node_name));
    port_index_t index = node_def_find_port_index(node_def, port_name);
    program_add_op(program, (op_t *) use_free_wire_op_new(node_def, index));
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
