#include "index.h"

void
call_program(vm_t *vm, const program_def_t *def) {
    frame_t *frame = frame_new(def->program);
    stack_push(vm->return_stack, frame);
    return;
}
