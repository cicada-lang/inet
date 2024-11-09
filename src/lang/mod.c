#include "index.h"

// A mod is a compilation unit,
// like the dictionary of forth,
// which stores specs.

struct mod_t {
    list_t *spec_list;
    list_t *rule_list;
};

mod_t *
mod_new(void) {
    mod_t *self = allocate(sizeof(mod_t));
    self->spec_list = list_new();
    // TODO setup spec_destroy
    self->rule_list = list_new();
    // TODO setup rule_destroy
    return self;
}

void
mod_destroy(mod_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        mod_t *self = *self_pointer;
        list_destroy(&self->spec_list);
        list_destroy(&self->rule_list);
        free(self);
        *self_pointer = NULL;
    }
}
