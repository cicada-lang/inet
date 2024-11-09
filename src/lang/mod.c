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
    self->rule_list = list_new();
    return self;
}
