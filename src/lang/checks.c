#include "index.h"

void
check_name_not_defined(
    const vm_t *vm,
    const char *name,
    const token_t *token
) {
    mod_t *mod = vm->mod;
    const spec_t *found = mod_find_spec(mod, name);
    if (found) {
        fprintf(vm->err, "[compiler-error] can not re-define name: %s\n", name);
        fprintf(vm->err, "[compiler-error] already defined to: ");
        spec_print(found, vm->err);
        fprintf(vm->err, "\n");
        fprintf(vm->err, "[src] %s\n", mod->src);
        code_print_context(vm->err, mod->string, token->start, token->end);
        exit(1);
    }
}

void
check_name_defined(
    const vm_t *vm,
    const char *name,
    const token_t *token
) {
    mod_t *mod = vm->mod;
    const spec_t *found = mod_find_spec(mod, name);
    if (!found) {
        fprintf(vm->err, "[compiler-error] undefined name: %s\n", name);
        fprintf(vm->err, "[src] %s\n", mod->src);
        code_print_context(vm->err, mod->string, token->start, token->end);
        exit(1);
    }
}

void
check_node_name_defined(
    const vm_t *vm,
    const char *name,
    const token_t *token
) {
    mod_t *mod = vm->mod;
    const spec_t *found = mod_find_spec(mod, name);
    if (!found) {
        fprintf(vm->err, "[compiler-error] undefined node name: %s\n", name);
        fprintf(vm->err, "[src] %s\n", mod->src);
        code_print_context(vm->err, mod->string, token->start, token->end);
        exit(1);
    }

    if (found->tag != NODE_SPEC) {
        fprintf(vm->err, "[compiler-error] expect name defined as node instead of: %s\n", spec_tag_name(found->tag));
        fprintf(vm->err, "[src] %s\n", mod->src);
        code_print_context(vm->err, mod->string, token->start, token->end);
        exit(1);
    }
}

void
check_port_name_defined(
    const vm_t *vm,
    const char *node_name,
    const char *port_name,
    const token_t *token
) {
    check_node_name_defined(vm, node_name, token);
    mod_t *mod = vm->mod;
    const spec_t *found = mod_find_spec(mod, node_name);
    const node_spec_t *spec = (node_spec_t *) found;
    for (port_index_t i = 0; i < spec->arity; i++) {
        port_spec_t *port_spec = spec->port_specs[i];
        if (string_equal(port_spec->name, port_name)) return;
    }

    fprintf(vm->err, "[compiler-error] undefined port name: %s\n", port_name);
    fprintf(vm->err, "[compiler-error] for node name: %s\n", node_name);
    fprintf(vm->err, "[src] %s\n", mod->src);
    code_print_context(vm->err, mod->string, token->start, token->end);
    exit(1);
}
