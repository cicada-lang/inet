#pragma once

typedef void (primitive_fn_t)(vm_t *vm);

struct primitive_def_t {
    char *name;
    primitive_fn_t *primitive_fn;
};

primitive_def_t *primitive_def_new(const char *name, primitive_fn_t *primitive_fn);
void primitive_def_destroy(primitive_def_t **self_pointer);
