#include "index.h"

void
emit_call(const mod_t *mod, function_t *function, const char *name) {
    const def_t *def = mod_find_def(mod, name);
    assert(def && "[emit_call] unknown name");
    function_add_op(function, (op_t *) call_op_new(def));
    return;
}

void
emit_connect(const mod_t *mod, function_t *function) {
    (void) mod;
    function_add_op(function, (op_t *) connect_op_new());
}

void
emit_use_free_wire(
    const mod_t *mod,
    function_t *function,
    const char *node_name,
    const char *port_name
) {
    const node_def_t *node_def = def_as_node_def(mod_find_def(mod, node_name));
    port_index_t index = node_def_find_port_index(node_def, port_name);
    function_add_op(function, (op_t *) use_free_wire_op_new(node_def, index));
}

void
emit_reconnect_free_wire(
    const mod_t *mod,
    function_t *function,
    const char *node_name,
    const char *port_name
) {
    emit_use_free_wire(mod, function, node_name, port_name);
    emit_connect(mod, function);
}
