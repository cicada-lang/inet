#include "index.h"

void
call(vm_t *vm, const def_t *def) {
    switch (def->kind) {
    case PRIMITIVE_DEF: {
        call_primitive(vm, def->as_primitive_def);
        return;
    }

    case FUNCTION_DEF: {
        call_function(vm, def->as_function_def);
        return;
    }

    case NODE_DEF: {
        call_node(vm, def->as_node_def);
        return;
    }
    }
}
