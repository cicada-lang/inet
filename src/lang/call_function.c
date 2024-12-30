#include "index.h"

void
call_function(vm_t *vm, const function_def_t *def) {
    frame_t *frame = frame_new(def->function);
    stack_push(vm->return_stack, frame);
    return;
}
