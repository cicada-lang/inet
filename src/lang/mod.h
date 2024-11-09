#pragma once

mod_t *mod_new(void);
void mod_destroy(mod_t **self_pointer);

const rule_t *mod_find_rule(const mod_t *self, const active_pair_t *active_pair);
