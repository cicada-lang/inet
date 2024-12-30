#include "index.h"

void
run_net(vm_t *vm) {
    while (!list_is_empty(vm->active_wire_list)) {
        step_net(vm);
    }
}

static void
collect_free_wires_from_node(vm_t *vm, node_t *node) {
    for (port_index_t i = 0; i < node->def->arity; i++) {
        if (!wire_is_principal(node->wires[i])) {
            wire_t *wire = node->wires[i];
            wire_free_from_node(wire);
            stack_push(vm->value_stack, wire);
        }
    }

    node_destroy(&node);
}

void
step_net(vm_t *vm) {
    wire_t *active_wire = list_pop(vm->active_wire_list);
    if (!active_wire) return;

    const rule_t *rule = mod_find_rule(
        vm->mod,
        active_wire,
        active_wire->opposite);
    if (!rule) return;

    node_t *first_node = active_wire->node;
    node_t *second_node = active_wire->opposite->node;

    if (first_node->def == rule->second_node_def &&
        second_node->def == rule->first_node_def)
    {
        first_node = active_wire->opposite->node;
        second_node = active_wire->node;
    }

    collect_free_wires_from_node(vm, first_node);
    collect_free_wires_from_node(vm, second_node);

    size_t base_length = stack_length(vm->return_stack);
    frame_t *frame = frame_new(rule->function);

    stack_push(vm->return_stack, frame);
    run_vm_until(vm, base_length);
}

void
run_vm_until(vm_t *vm, size_t base_length) {
    if (vm->log_level > 0) {
        vm_print(vm, stdout);
        fprintf(stdout, "\n");
    }

    while (stack_length(vm->return_stack) > base_length) {
        step_vm(vm);

        if (vm->log_level > 0) {
            vm_print(vm, stdout);
            fprintf(stdout, "\n");
        }
    }
}

void
step_vm(vm_t *vm) {
    if (stack_is_empty(vm->return_stack)) return;

    frame_t *frame = stack_pop(vm->return_stack);
    if (frame_is_finished(frame)) return;

    op_t *op = frame_fetch_op(frame);
    // proper tail-call = do not push finished frame.
    bool finished = frame_is_finished(frame);
    if (!finished) stack_push(vm->return_stack, frame);
    execute_operation(vm, frame, op);
    if (finished) frame_destroy(&frame);
}
