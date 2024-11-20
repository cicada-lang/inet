#include "index.h"

mod_t *
mod_new(const char *src, const char *text) {
    mod_t *self = allocate(sizeof(mod_t));

    self->src = src;
    self->text = text;

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
mod_find_rule(
    const mod_t *self,
    const wire_t *first_wire,
    const wire_t *second_wire
) {
    rule_t *rule = list_start(self->rule_list);
    while (rule) {
        if (rule_match_wire_pair(rule, first_wire, second_wire)) return rule;
        rule = list_next(self->rule_list);
    }

    return NULL;
}

void
mod_define(mod_t *self, spec_t *spec) {
    list_push(self->spec_list, spec);
}

void
mod_define_rule(
    mod_t *self,
    const char *first_name,
    const char *second_name,
    program_t *program
) {
    const node_spec_t *first_node_spec =
        node_spec_cast(mod_find_spec(self, first_name));
    const node_spec_t *second_node_spec =
        node_spec_cast(mod_find_spec(self, second_name));

    rule_t *rule = rule_new(first_node_spec, second_node_spec, program);
    list_push(self->rule_list, rule);
}

void
mod_print(const mod_t *self, file_t *file) {
    fprintf(file, "<mod spec-count=\"%lu\" rule-count=\"%lu\">\n",
            list_length(self->spec_list),
            list_length(self->rule_list));

    spec_t *spec = list_start(self->spec_list);
    while (spec) {
        spec_print(spec, file);
        fprintf(file, "\n");
        spec = list_next(self->spec_list);
    }

    rule_t *rule = list_start(self->rule_list);
    while (rule) {
        rule_print(rule, file);
        fprintf(file, "\n");
        rule = list_next(self->rule_list);
    }

    fprintf(file, "</mod>\n");
}
