#pragma once

#define PRIMITIVE_DEF ((uint8_t) 0)

typedef void (primitive_fn_t)(vm_t *vm);

struct primitive_def_t {
    def_kind_t kind;
    char *name;
    primitive_fn_t *primitive_fn;
};

primitive_def_t *primitive_def_new(const char *name, primitive_fn_t *primitive_fn);
void primitive_def_destroy(primitive_def_t **self_pointer);
