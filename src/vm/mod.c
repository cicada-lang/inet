#include "index.h"

mod_t *
mod_new(const char *src, const char *string) {
    mod_t *self = new(mod_t);

    self->src = src;
    self->string = string;

    self->def_list = list_new_with((destroy_fn_t *) def_destroy);
    self->rule_list = list_new_with((destroy_fn_t *) rule_destroy);

    return self;
}

void
mod_destroy(mod_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        mod_t *self = *self_pointer;
        list_destroy(&self->def_list);
        list_destroy(&self->rule_list);
        free(self);
        *self_pointer = NULL;
    }
}

const def_t *
mod_find_def(const mod_t *self, const char *name) {
    def_t *def = list_first(self->def_list);
    while (def) {
        if (string_equal(def_name(def), name)) return def;
        def = list_next(self->def_list);
    }

    return NULL;
}

const rule_t *
mod_find_rule(
    const mod_t *self,
    const wire_t *first_wire,
    const wire_t *second_wire
) {
    rule_t *rule = list_first(self->rule_list);
    while (rule) {
        if (rule_match_wire_pair(rule, first_wire, second_wire)) return rule;
        rule = list_next(self->rule_list);
    }

    return NULL;
}

void
mod_define(mod_t *self, def_t *def) {
    list_push(self->def_list, def);
}

void
mod_define_rule(
    mod_t *self,
    const char *first_name,
    const char *second_name,
    function_t *function
) {
    const node_def_t *first_node_def =
        def_as_node_def(mod_find_def(self, first_name));
    const node_def_t *second_node_def =
        def_as_node_def(mod_find_def(self, second_name));

    rule_t *rule = rule_new(first_node_def, second_node_def, function);
    list_push(self->rule_list, rule);
}

void
mod_print(const mod_t *self, file_t *file) {
    fprintf(file, "<mod def-count=\"%lu\" rule-count=\"%lu\">\n",
            list_length(self->def_list),
            list_length(self->rule_list));

    def_t *def = list_first(self->def_list);
    while (def) {
        def_print(def, file);
        fprintf(file, "\n");
        def = list_next(self->def_list);
    }

    rule_t *rule = list_first(self->rule_list);
    while (rule) {
        rule_print(rule, file);
        fprintf(file, "\n");
        rule = list_next(self->rule_list);
    }

    fprintf(file, "</mod>\n");
}
