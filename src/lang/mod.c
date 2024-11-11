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

const spec_t *
mod_find_spec(const mod_t *self, const char *name) {
    spec_t *spec = list_start(self->spec_list);
    while (spec) {
        if (string_equal(spec_name(spec), name)) return spec;
        spec = list_next(self->spec_list);
    }

    return NULL;
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

void
mod_define(mod_t *self, spec_t *spec) {
    list_push(self->spec_list, spec);
}

// void
// mod_define_rule(
//     mod_t *self,
//     const char *first_name,
//     const char *second_name,
//     program_t *program
// ) {
//     node_spec_t *first_node_spec = ;
//     node_spec_t *second_node_spec = ;
//     rule_t *rule = rule_new(first_node_spec, second_node_spec, program);
//     list_push(self->rule_list, rule);
// }
