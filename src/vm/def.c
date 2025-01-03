#include "index.h"

def_t *
def_from_primitive_def(primitive_def_t *primitive_def) {
    def_t *self = new(def_t);
    self->kind = PRIMITIVE_DEF;
    self->as_primitive_def = primitive_def;
    return self;
}

def_t *
def_from_function_def(function_def_t *function_def) {
    def_t *self = new(def_t);
    self->kind = FUNCTION_DEF;
    self->as_function_def = function_def;
    return self;
}

def_t *
def_from_constant_def(constant_def_t *constant_def) {
    def_t *self = new(def_t);
    self->kind = CONSTANT_DEF;
    self->as_constant_def = constant_def;
    return self;
}

def_t *
def_from_node_def(node_def_t *node_def) {
    def_t *self = new(def_t);
    self->kind = NODE_DEF;
    self->as_node_def = node_def;
    return self;
}


void
def_destroy(def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        def_t *self = *self_pointer;

        switch (self->kind) {
        case PRIMITIVE_DEF: {
            primitive_def_destroy(&self->as_primitive_def);
            break;
        }

        case FUNCTION_DEF: {
            function_def_destroy(&self->as_function_def);
            break;
        }

        case CONSTANT_DEF: {
            constant_def_destroy(&self->as_constant_def);
            break;
        }

        case NODE_DEF: {
            node_def_destroy(&self->as_node_def);
            break;
        }
        }

        free(self);
        *self_pointer = NULL;
    }
}

const char *
def_name(const def_t *def) {
    switch (def->kind) {
    case PRIMITIVE_DEF: {
        return def->as_primitive_def->name;
    }

    case FUNCTION_DEF: {
        return def->as_function_def->name;
    }

    case CONSTANT_DEF: {
        return def->as_constant_def->name;
    }

    case NODE_DEF: {
        return def->as_node_def->name;
    }
    }

    assert(false);
}

const char *
def_kind_name(def_kind_t kind) {
    switch (kind) {
    case PRIMITIVE_DEF: {
        return "primitive";
    }

    case FUNCTION_DEF: {
        return "function";
    }

    case CONSTANT_DEF: {
        return "constant";
    }

    case NODE_DEF: {
        return "node";
    }
    }

    assert(false);
}

void
def_print(const def_t *def, file_t *file) {
    switch (def->kind) {
    case PRIMITIVE_DEF: {
        fprintf(file, "define-primitive %s", def->as_primitive_def->name);
        return;
    }

    case FUNCTION_DEF: {
        fprintf(file, "define %s ", def->as_function_def->name);
        function_print(def->as_function_def->function, file);
        return;
    }

    case CONSTANT_DEF: {
        fprintf(file, "define-constant %s ", def->as_constant_def->name);
        return;
    }

    case NODE_DEF: {
        fprintf(file, "define-node %s ", def->as_node_def->name);
        for (port_index_t i = 0; i < def->as_node_def->input_arity; i++) {
            port_def_t *port_def = def->as_node_def->port_defs[i];
            if (port_def->is_principal) {
                fprintf(file, "%s! ", port_def->name);
            } else {
                fprintf(file, "%s ", port_def->name);
            }
        }

        fprintf(file, "-- ");

        for (port_index_t c = 0; c < def->as_node_def->output_arity; c++) {
            port_index_t i = def->as_node_def->input_arity + c;
            port_def_t *port_def = def->as_node_def->port_defs[i];
            if (port_def->is_principal) {
                fprintf(file, "%s! ", port_def->name);
            } else {
                fprintf(file, "%s ", port_def->name);
            }
        }

        return;
    }
    }

    assert(false);
}
