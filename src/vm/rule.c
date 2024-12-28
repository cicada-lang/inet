#include "index.h"

rule_t *
rule_new(
    const node_def_t *first_node_def,
    const node_def_t *second_node_def,
    function_t *function
) {
    rule_t *self = new(rule_t);
    self->first_node_def = first_node_def;
    self->second_node_def = second_node_def;
    self->function = function;
    return self;
}

void
rule_destroy(rule_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        rule_t *self = *self_pointer;
        function_destroy(&self->function);
        free(self);
        *self_pointer = NULL;
    }
}

bool
rule_match_wire_pair(
    const rule_t *self,
    const wire_t *first_wire,
    const wire_t *second_wire
) {
    return (((self->first_node_def == first_wire->node->def) &&
             (self->second_node_def == second_wire->node->def)) ||
            ((self->first_node_def == second_wire->node->def) &&
             (self->second_node_def == first_wire->node->def)));
}

void
rule_print(const rule_t *self, file_t *file) {
    fprintf(file, "! (%s)-(%s) ",
            self->first_node_def->name,
            self->second_node_def->name);
    function_print(self->function, file);
}
