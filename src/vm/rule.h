#pragma once

struct rule_t {
    const node_def_t *first_node_def;
    const node_def_t *second_node_def;
    function_t *function;
};

rule_t *rule_new(
    const node_def_t *first_node_def,
    const node_def_t *second_node_def,
    function_t *function);
void rule_destroy(rule_t **self_pointer);
bool rule_match_wire_pair(
    const rule_t *self,
    const wire_t *first_wire,
    const wire_t *second_wire);

void rule_print(const rule_t *self, file_t *file);
