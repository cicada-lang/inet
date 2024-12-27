#include "index.h"

void
call(vm_t *vm, const def_t *def) {
    switch (def->kind) {
    case PRIMITIVE_DEF: {
        call_primitive(vm, def->as_primitive_def);
        return;
    }

    case PROGRAM_DEF: {
        call_program(vm, def->as_program_def);
        return;
    }

    case NODE_DEF: {
        call_node(vm, def->as_node_def);
        return;
    }
    }
}
