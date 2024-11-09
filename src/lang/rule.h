#pragma once

struct rule_t {
    const node_spec_t *first_node_spec;
    const node_spec_t *second_node_spec;
    program_t *program;
};

rule_t *rule_new(
    const node_spec_t *first_node_spec,
    const node_spec_t *second_node_spec,
    program_t *program);
void rule_destroy(rule_t **self_pointer);
bool rule_match_active_pair(const rule_t *self, const active_pair_t *active_pair);
