#pragma once

void run_net(vm_t *self);
void step_net(vm_t *self);
void run_vm_until_until(vm_t *self, size_t base_length);
void step_vm(vm_t *self);
