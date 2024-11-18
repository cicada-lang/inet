#pragma once

typedef void (builtin_t)(worker_t *worker);

struct builtin_spec_t {
    spec_tag_t tag;
    char *name;
    builtin_t *builtin;
};

builtin_spec_t *builtin_spec_new(const char *name, builtin_t *builtin);
void builtin_spec_destroy(builtin_spec_t **self_pointer);

const builtin_spec_t *builtin_spec_cast(const spec_t *spec);
