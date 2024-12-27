#include "index.h"

void
call(vm_t *vm, const def_t *unknown_def) {
    switch (unknown_def->kind) {
    case PRIMITIVE_DEF: {
        call_primitive(vm, (primitive_def_t *) unknown_def);
        return;
    }

    case PROGRAM_DEF: {
        call_program(vm, (program_def_t *) unknown_def);
        return;
    }

    case NODE_DEF: {
        call_node(vm, (node_def_t *) unknown_def);
        return;
    }
    }
}
