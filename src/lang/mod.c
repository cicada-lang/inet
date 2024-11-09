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
    list_set_item_destructor(
        self->spec_list,
        (list_item_destructor_t *) spec_destroy);

    self->rule_list = list_new();
    list_set_item_destructor(
        self->rule_list,
        (list_item_destructor_t *) rule_destroy);

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

const rule_t *
mod_find_rule(const mod_t *self, const active_pair_t *active_pair) {
    rule_t *rule = list_start(self->rule_list);
    while (rule) {
        if (rule_match_active_pair(rule, active_pair)) return rule;
        rule = list_next(self->rule_list);
    }

    return NULL;
}
