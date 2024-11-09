#pragma once

rule_t *rule_new(
    const node_spec_t *first_node_spec,
    const node_spec_t *second_node_spec,
    program_t *program);
void rule_destroy(rule_t **self_pointer);
