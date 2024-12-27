#pragma once

void call(vm_t *vm, const def_t *unknown_def);

void call_primitive(vm_t *vm, const primitive_def_t *def);
void call_program(vm_t *vm, const program_def_t *def);
void call_node(vm_t *vm, const node_def_t *def);
