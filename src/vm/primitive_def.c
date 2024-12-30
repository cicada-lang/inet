#include "index.h"

static primitive_def_t *
primitive_def_new(const char *name) {
    primitive_def_t *self = new(primitive_def_t);
    self->name = string_copy(name);
    return self;
}

primitive_def_t *
primitive_def_from_vm_fn(const char *name, primitive_vm_fn_t *primitive_vm_fn) {
    primitive_def_t *self = primitive_def_new(name);
    self->fn_kind = PRIMITIVE_VM_FN;
    self->primitive_vm_fn = primitive_vm_fn;
    return self;
}

primitive_def_t *
primitive_def_from_0_fn(const char *name, primitive_0_fn_t *primitive_0_fn) {
    primitive_def_t *self = primitive_def_new(name);
    self->fn_kind = PRIMITIVE_0_FN;
    self->primitive_0_fn = primitive_0_fn;
    return self;
}

primitive_def_t *
primitive_def_from_1_fn(const char *name, primitive_1_fn_t *primitive_1_fn) {
    primitive_def_t *self = primitive_def_new(name);
    self->fn_kind = PRIMITIVE_1_FN;
    self->primitive_1_fn = primitive_1_fn;
    return self;
}

primitive_def_t *
primitive_def_from_2_fn(const char *name, primitive_2_fn_t *primitive_2_fn) {
    primitive_def_t *self = primitive_def_new(name);
    self->fn_kind = PRIMITIVE_2_FN;
    self->primitive_2_fn = primitive_2_fn;
    return self;
}

primitive_def_t *
primitive_def_from_3_fn(const char *name, primitive_3_fn_t *primitive_3_fn) {
    primitive_def_t *self = primitive_def_new(name);
    self->fn_kind = PRIMITIVE_3_FN;
    self->primitive_3_fn = primitive_3_fn;
    return self;
}

primitive_def_t *
primitive_def_from_4_fn(const char *name, primitive_4_fn_t *primitive_4_fn) {
    primitive_def_t *self = primitive_def_new(name);
    self->fn_kind = PRIMITIVE_4_FN;
    self->primitive_4_fn = primitive_4_fn;
    return self;
}

void
primitive_def_destroy(primitive_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        primitive_def_t *self = *self_pointer;
        string_destroy(&self->name);
        free(self);
        *self_pointer = NULL;
    }
}
