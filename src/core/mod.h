#pragma once

// A mod is a compilation unit,
// like the dictionary of forth.

struct mod_t {
    const char *src;
    const char *text;
    list_t *spec_list;
    list_t *rule_list;
};

mod_t *mod_new(const char *src, const char *text);
void mod_destroy(mod_t **self_pointer);

const spec_t *mod_find_spec(const mod_t *self, const char *name);
const rule_t *mod_find_rule(
    const mod_t *self,
    const wire_t *first_wire,
    const wire_t *second_wire);
void mod_define(mod_t *self, spec_t *spec);
void mod_define_rule(mod_t *self, const char *first_name, const char *second_name, program_t *program);

void mod_print(const mod_t *self, file_t *file);
