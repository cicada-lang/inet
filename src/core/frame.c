#include "index.h"

// The aim of having two free wire groups in frame
// is to reference free wire in them by `use_free_wire_op_t`.

typedef struct free_wire_group_t free_wire_group_t;

struct frame_t {
    size_t program_counter;
    const program_t *program;
    free_wire_group_t *first_free_wire_group;
    free_wire_group_t *second_free_wire_group;
};

struct free_wire_group_t {
    const node_spec_t *node_spec;
    wire_t **wires;
};

static free_wire_group_t *
free_wire_group_new(const node_spec_t *node_spec) {
    free_wire_group_t *self = allocate(sizeof(free_wire_group_t));
    self->node_spec = node_spec;
    self->wires = allocate_pointers(node_spec->arity);
    return self;
}

static void
free_wire_group_destroy(free_wire_group_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        free_wire_group_t *self = *self_pointer;
        free(self->wires);
        // Does NOT own wires in `wires`.
        free(self);
        *self_pointer = NULL;
    }
}

frame_t *
frame_new(const program_t *program) {
    frame_t *self = allocate(sizeof(frame_t));
    self->program_counter = 0;
    self->program = program;
    return self;
}

void
frame_destroy(frame_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        frame_t *self = *self_pointer;
        free_wire_group_destroy(&self->first_free_wire_group);
        free_wire_group_destroy(&self->second_free_wire_group);
        free(self);
        *self_pointer = NULL;
    }
}

static free_wire_group_t *
collect_free_wires_from_node(node_t *node) {
    free_wire_group_t *free_wire_group = free_wire_group_new(node->spec);
    for (port_index_t i = 0; i < node->spec->arity; i++) {
        if (wire_is_principal(node->wires[i])) {
            free_wire_group->wires[i] = NULL;
        } else {
            wire_t *wire = node->wires[i];
            wire_free_from_node(wire);
            free_wire_group->wires[i] = wire;
        }
    }

    node_destroy(&node);
    return free_wire_group;
}

void
frame_collect_free_wires(frame_t *self, wire_t *wire) {
    wire_t *first_wire = wire;
    wire_t *second_wire = wire->opposite_wire;

    self->first_free_wire_group = collect_free_wires_from_node(first_wire->node);
    self->second_free_wire_group = collect_free_wires_from_node(second_wire->node);

    wire_destroy(&first_wire);
    wire_destroy(&second_wire);
}

wire_t *
frame_use_free_wire(
    frame_t *self,
    const node_spec_t *node_spec,
    port_index_t index
) {
    if (node_spec == self->first_free_wire_group->node_spec) {
        wire_t *free_wire = self->first_free_wire_group->wires[index];
        self->first_free_wire_group->wires[index] = NULL;
        if (!free_wire) {
            fprintf(stderr,
                    "[frame_use_free_wire] (%s) no wire at index: %i",
                    node_spec->name,
                    index);
            assert(free_wire);
        }

        return free_wire;
    }

    if (node_spec == self->second_free_wire_group->node_spec) {
        wire_t *free_wire = self->second_free_wire_group->wires[index];
        self->second_free_wire_group->wires[index] = NULL;
        if (!free_wire) {
            fprintf(stderr,
                    "[frame_use_free_wire] (%s) no wire at index: %i",
                    node_spec->name,
                    index);
            assert(free_wire);
        }

        return free_wire;
    }

    assert(false);
}

bool
frame_is_finished(const frame_t *self) {
    return self->program_counter == program_length(self->program);
}

op_t *
frame_fetch_op(frame_t *self) {
    op_t *op = program_get_op(self->program, self->program_counter);
    self->program_counter++;
    return op;
}

static void
free_wire_group_print(const free_wire_group_t *free_wire_group, file_t *file) {
    for (port_index_t i = 0; i < free_wire_group->node_spec->arity; i++) {
        wire_t *free_wire = free_wire_group->wires[i];
        if (!free_wire) continue;

        fprintf(file, "(%s)-%s => ",
                free_wire_group->node_spec->name,
                free_wire_group->node_spec->port_specs[i]->name);
        wire_print_reverse(free_wire, file);
        fprintf(file, "\n");
    }
}

void
frame_print(const frame_t *self, file_t *file) {
    fprintf(file, "<frame>\n");

    fprintf(file, "<program>\n");
    fprintf(file, ". ");
    program_print_with_program_counter(self->program, file, self->program_counter);
    fprintf(file, "\n");
    fprintf(file, "</program>\n");

    fprintf(file, "<local-free-wires>\n");
    if (self->first_free_wire_group)
        free_wire_group_print(self->first_free_wire_group, file);
    if (self->second_free_wire_group)
        free_wire_group_print(self->second_free_wire_group, file);
    fprintf(file, "</local-free-wires>\n");

    fprintf(file, "</frame>\n");
}
