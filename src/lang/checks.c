#include "index.h"

void
check_name_not_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token
) {
    mod_t *mod = worker->mod;
    const spec_t *found = mod_find_spec(mod, name);
    if (found) {
        fprintf(worker->err, "[compiler-error] can not re-define name: %s\n", name);
        fprintf(worker->err, "[compiler-error] already defined to: ");
        spec_print(found, worker->err);
        fprintf(worker->err, "\n");
        fprintf(worker->err, "[src] %s\n", mod->src);
        text_print_context(worker->err, mod->text, token->start, token->end);
        exit(1);
    }
}

void
check_name_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token
) {
    mod_t *mod = worker->mod;
    const spec_t *found = mod_find_spec(mod, name);
    if (!found) {
        fprintf(worker->err, "[compiler-error] undefined name: %s\n", name);
        fprintf(worker->err, "[src] %s\n", mod->src);
        text_print_context(worker->err, mod->text, token->start, token->end);
        exit(1);
    }
}

void
check_name_defined_to_node_spec(
    const worker_t *worker,
    const char *name,
    const token_t *token
) {
    mod_t *mod = worker->mod;
    const spec_t *found = mod_find_spec(mod, name);
    if (!found) {
        fprintf(worker->err, "[compiler-error] undefined node name: %s\n", name);
        fprintf(worker->err, "[src] %s\n", mod->src);
        text_print_context(worker->err, mod->text, token->start, token->end);
        exit(1);
    }

    if (found->tag != NODE_SPEC) {
        fprintf(worker->err, "[compiler-error] expect name defined as node instead of: %s\n", spec_tag_name(found->tag));
        fprintf(worker->err, "[src] %s\n", mod->src);
        text_print_context(worker->err, mod->text, token->start, token->end);
        exit(1);
    }
}
