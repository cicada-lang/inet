#pragma once

typedef void (builtin_fn_t)(vm_t *vm);

struct builtin_def_t {
    def_kind_t kind;
    char *name;
    builtin_fn_t *builtin_fn;
};

builtin_def_t *builtin_def_new(const char *name, builtin_fn_t *builtin_fn);
void builtin_def_destroy(builtin_def_t **self_pointer);

const builtin_def_t *builtin_def_cast(const def_t *def);
