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
