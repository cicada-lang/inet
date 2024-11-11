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
    }

    assert(false);
}
