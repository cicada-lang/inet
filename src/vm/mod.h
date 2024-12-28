#pragma once

// A mod is a compilation unit,
// like the dictionary of forth.

struct mod_t {
    const char *src;
    const char *string;
    list_t *def_list;
    list_t *rule_list;
};

mod_t *mod_new(const char *src, const char *string);
void mod_destroy(mod_t **self_pointer);

const def_t *mod_find_def(const mod_t *self, const char *name);
const rule_t *mod_find_rule(
    const mod_t *self,
    const wire_t *first_wire,
    const wire_t *second_wire);
void mod_define(mod_t *self, def_t *def);
void mod_define_rule(mod_t *self, const char *first_name, const char *second_name, function_t *function);

void mod_print(const mod_t *self, file_t *file);
