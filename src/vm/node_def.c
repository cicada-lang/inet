#include "index.h"

port_def_t *
port_def_new(const char *name, bool is_principal) {
    port_def_t *self = new(port_def_t);
    self->name = string_copy(name);
    self->is_principal = is_principal;
    return self;
}

void
port_def_destroy(port_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        port_def_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

node_def_t *
node_def_new(
    const char *name,
    port_index_t input_arity,
    port_index_t output_arity
) {
    node_def_t *self = new(node_def_t);
    self->kind = NODE_DEF;
    self->name = string_copy(name);
    self->input_arity = input_arity;
    self->output_arity = output_arity;
    self->arity = input_arity + output_arity;
    self->port_defs = allocate_pointers(self->arity);
    return self;
}

void
node_def_destroy(node_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_def_t *self = *self_pointer;
        for (port_index_t i = 0; i < self->arity; i++) {
            port_def_t *port_def = self->port_defs[i];
            if (port_def) {
                port_def_destroy(&port_def);
            }
        }

        free(self->port_defs);
        free(self);
        *self_pointer = NULL;
    }
}

const node_def_t *
node_def_cast(const def_t *def) {
    assert(def);
    assert(def->kind == NODE_DEF);
    return (node_def_t *)def;
}

port_index_t
node_def_find_port_index(
    const node_def_t *node_def,
    const char *port_name
) {
    for (port_index_t i = 0; i < node_def->arity; i++) {
        port_def_t *port_def = node_def->port_defs[i];
        if (string_equal(port_def->name, port_name))
            return i;
    }

    printf("[node_def_find_port_index] fail to find index of node_name: %s, port_name: %s\n",
           node_def->name,
           port_name);

    assert(false);
}
