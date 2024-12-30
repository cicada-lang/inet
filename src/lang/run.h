#pragma once

void run_net(vm_t *vm);
void step_net(vm_t *vm);
void run_vm_until_until(vm_t *vm, size_t base_length);
void step_vm(vm_t *vm);
