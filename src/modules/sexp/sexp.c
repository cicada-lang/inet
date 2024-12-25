#include "index.h"

atom_sexp_t *
atom_sexp_new(const token_t *token) {
    atom_sexp_t *self = new(atom_sexp_t);
    self->kind = ATOM_SEXP;
    self->token = token;
    return self;
}

void
atom_sexp_destroy(atom_sexp_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        atom_sexp_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

list_sexp_t *
list_sexp_new(void) {
    list_sexp_t *self = new(list_sexp_t);
    self->kind = LIST_SEXP;
    self->sexp_list = list_new_with((destroy_fn_t *) sexp_destroy);
    return self;
}

void
list_sexp_destroy(list_sexp_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        list_sexp_t *self = *self_pointer;
        list_destroy(&self->sexp_list);
        free(self);
        *self_pointer = NULL;
    }
}

void
sexp_destroy(sexp_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        sexp_t *self = *self_pointer;
        switch (self->kind) {
        case ATOM_SEXP: {
            atom_sexp_destroy((atom_sexp_t **) self_pointer);
            return;
        }

        case LIST_SEXP: {
            list_sexp_destroy((list_sexp_t **) self_pointer);
            return;
        }
        }
    }
}
