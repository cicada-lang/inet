#include "index.h"

void
spec_destroy(spec_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        spec_t *self = *self_pointer;
        switch (self->tag) {
        case NODE_SPEC:
            node_spec_destroy((node_spec_t **) self_pointer);
            return;
        case PROGRAM_SPEC:
            program_spec_destroy((program_spec_t **) self_pointer);
            return;
        }
    }
}
