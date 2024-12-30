#pragma once

void execute_operation(vm_t *self, frame_t *frame, op_t *op);
void execute_one(vm_t *vm);
void execute_all(vm_t *vm);
