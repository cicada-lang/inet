#include "index.h"

void
call(vm_t *vm, const def_t *unknown_def) {
    switch (unknown_def->kind) {
    case PRIMITIVE_DEF: {
        primitive_def_t *def = (primitive_def_t *) unknown_def;
        def->primitive_fn(vm);
        return;
    }

    case PROGRAM_DEF: {
        program_def_t *def = (program_def_t *) unknown_def;
        frame_t *frame = frame_new(def->program);
        stack_push(vm->return_stack, frame);
        return;
    }

    case NODE_DEF: {
        call_node(vm, (node_def_t *) unknown_def);
        return;
    }
    }
}
