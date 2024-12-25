#include "index.h"

void
spec_destroy(spec_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        spec_t *self = *self_pointer;
        switch (self->tag) {
        case NODE_SPEC: {
            node_spec_destroy((node_spec_t **) self_pointer);
            return;
        }

        case PROGRAM_SPEC: {
            program_spec_destroy((program_spec_t **) self_pointer);
            return;
        }

        case BUILTIN_SPEC: {
            builtin_spec_destroy((builtin_spec_t **) self_pointer);
            return;
        }
        }
    }
}

const char *
spec_name(spec_t *unknown_spec) {
    switch (unknown_spec->tag) {
    case NODE_SPEC: {
        node_spec_t *spec = (node_spec_t *) unknown_spec;
        return spec->name;
    }

    case PROGRAM_SPEC: {
        program_spec_t *spec = (program_spec_t *) unknown_spec;
        return spec->name;
    }

    case BUILTIN_SPEC: {
        builtin_spec_t *spec = (builtin_spec_t *) unknown_spec;
        return spec->name;
    }
    }

    assert(false);
}

const char *
spec_tag_name(spec_tag_t tag) {
    switch (tag) {
    case NODE_SPEC: {
        return "node";
    }

    case PROGRAM_SPEC: {
        return "program";
    }

    case BUILTIN_SPEC: {
        return "builtin";
    }
    }

    assert(false);
}

void
spec_print(const spec_t *unknown_spec, file_t *file) {
    switch (unknown_spec->tag) {
    case NODE_SPEC: {
        node_spec_t *spec = (node_spec_t *) unknown_spec;
        fprintf(file, "* (%s) ", spec->name);
        for (port_index_t i = 0; i < spec->input_arity; i++) {
            port_spec_t *port_spec = spec->port_specs[i];
            if (port_spec->is_principal) {
                fprintf(file, "%s! ", port_spec->name);
            } else {
                fprintf(file, "%s ", port_spec->name);
            }
        }

        fprintf(file, "-- ");

        for (port_index_t c = 0; c < spec->output_arity; c++) {
            port_index_t i = spec->input_arity + c;
            port_spec_t *port_spec = spec->port_specs[i];
            if (port_spec->is_principal) {
                fprintf(file, "%s! ", port_spec->name);
            } else {
                fprintf(file, "%s ", port_spec->name);
            }
        }

        return;
    }

    case PROGRAM_SPEC: {
        program_spec_t *spec = (program_spec_t *) unknown_spec;
        fprintf(file, "= %s ", spec->name);
        program_print(spec->program, file);
        return;
    }

    case BUILTIN_SPEC: {
        builtin_spec_t *spec = (builtin_spec_t *) unknown_spec;
        fprintf(file, "%s", spec->name);
        return;
    }
    }

    assert(false);
}
