#pragma once

typedef void (builtin_fn_t)(worker_t *worker);

struct builtin_spec_t {
    spec_tag_t tag;
    char *name;
    builtin_fn_t *builtin_fn;
};

builtin_spec_t *builtin_spec_new(const char *name, builtin_fn_t *builtin_fn);
void builtin_spec_destroy(builtin_spec_t **self_pointer);

const builtin_spec_t *builtin_spec_cast(const spec_t *spec);
