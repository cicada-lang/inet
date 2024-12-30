#include "index.h"

void
call_primitive(vm_t *vm, const primitive_def_t *def) {
    switch (def->fn_kind) {
    case PRIMITIVE_VM_FN: {
        def->primitive_vm_fn(vm);
        return;
    }

    case PRIMITIVE_0_FN: {
        value_t result = def->primitive_0_fn();
        if (result != NULL)
            stack_push(vm->value_stack, result);
        return;
    }

    case PRIMITIVE_1_FN: {
        value_t x = stack_pop(vm->value_stack);
        value_t result = def->primitive_1_fn(x);
        if (result != NULL)
            stack_push(vm->value_stack, result);
        return;
    }

    case PRIMITIVE_2_FN: {
        value_t y = stack_pop(vm->value_stack);
        value_t x = stack_pop(vm->value_stack);
        value_t result = def->primitive_2_fn(x, y);
        if (result != NULL)
            stack_push(vm->value_stack, result);
        return;
    }

    case PRIMITIVE_3_FN: {
        value_t z = stack_pop(vm->value_stack);
        value_t y = stack_pop(vm->value_stack);
        value_t x = stack_pop(vm->value_stack);
        value_t result = def->primitive_3_fn(x, y, z);
        if (result != NULL)
            stack_push(vm->value_stack, result);
        return;
    }

    case PRIMITIVE_4_FN: {
        value_t w = stack_pop(vm->value_stack);
        value_t z = stack_pop(vm->value_stack);
        value_t y = stack_pop(vm->value_stack);
        value_t x = stack_pop(vm->value_stack);
        value_t result = def->primitive_4_fn(x, y, z, w);
        if (result != NULL)
            stack_push(vm->value_stack, result);
        return;
    }
    }
}
