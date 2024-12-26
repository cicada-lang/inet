#include "index.h"

void
def_destroy(def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        def_t *self = *self_pointer;
        switch (self->kind) {
        case NODE_DEF_KIND: {
            node_def_destroy((node_def_t **) self_pointer);
            return;
        }

        case PROGRAM_DEF_KIND: {
            program_def_destroy((program_def_t **) self_pointer);
            return;
        }

        case PRIMITIVE_DEF_KIND: {
            primitive_def_destroy((primitive_def_t **) self_pointer);
            return;
        }
        }
    }
}

const char *
def_name(const def_t *unknown_def) {
    switch (unknown_def->kind) {
    case NODE_DEF_KIND: {
        node_def_t *def = (node_def_t *) unknown_def;
        return def->name;
    }

    case PROGRAM_DEF_KIND: {
        program_def_t *def = (program_def_t *) unknown_def;
        return def->name;
    }

    case PRIMITIVE_DEF_KIND: {
        primitive_def_t *def = (primitive_def_t *) unknown_def;
        return def->name;
    }
    }

    assert(false);
}

const char *
def_kind_name(def_kind_t kind) {
    switch (kind) {
    case NODE_DEF_KIND: {
        return "node";
    }

    case PROGRAM_DEF_KIND: {
        return "program";
    }

    case PRIMITIVE_DEF_KIND: {
        return "primitive";
    }
    }

    assert(false);
}

void
def_print(const def_t *unknown_def, file_t *file) {
    switch (unknown_def->kind) {
    case NODE_DEF_KIND: {
        node_def_t *def = (node_def_t *) unknown_def;
        fprintf(file, "* (%s) ", def->name);
        for (port_index_t i = 0; i < def->input_arity; i++) {
            port_def_t *port_def = def->port_defs[i];
            if (port_def->is_principal) {
                fprintf(file, "%s! ", port_def->name);
            } else {
                fprintf(file, "%s ", port_def->name);
            }
        }

        fprintf(file, "-- ");

        for (port_index_t c = 0; c < def->output_arity; c++) {
            port_index_t i = def->input_arity + c;
            port_def_t *port_def = def->port_defs[i];
            if (port_def->is_principal) {
                fprintf(file, "%s! ", port_def->name);
            } else {
                fprintf(file, "%s ", port_def->name);
            }
        }

        return;
    }

    case PROGRAM_DEF_KIND: {
        program_def_t *def = (program_def_t *) unknown_def;
        fprintf(file, "= %s ", def->name);
        program_print(def->program, file);
        return;
    }

    case PRIMITIVE_DEF_KIND: {
        primitive_def_t *def = (primitive_def_t *) unknown_def;
        fprintf(file, "%s", def->name);
        return;
    }
    }

    assert(false);
}
