#include "index.h"

rule_t *
rule_new(
    const node_spec_t *first_node_spec,
    const node_spec_t *second_node_spec,
    program_t *program
    ) {
    rule_t *self = allocate(sizeof(rule_t));
    self->first_node_spec = first_node_spec;
    self->second_node_spec = second_node_spec;
    self->program = program;
    return self;
}

void
rule_destroy(rule_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        rule_t *self = *self_pointer;
        program_destroy(&self->program);
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
    return (((self->first_node_spec == first_wire->node->spec) &&
             (self->second_node_spec == second_wire->node->spec)) ||
            ((self->first_node_spec == second_wire->node->spec) &&
             (self->second_node_spec == first_wire->node->spec)));
}

void
rule_print(const rule_t *self, file_t *file) {
    fprintf(file, "! (%s)-(%s) ",
            self->first_node_spec->name,
            self->second_node_spec->name);
    program_print(self->program, file);
}
