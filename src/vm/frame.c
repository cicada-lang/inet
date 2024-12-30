#include "index.h"

// The aim of having two free wire groups in frame
// is to reference free wire in them by `use_free_wire_op_t`.

typedef struct free_wire_group_t free_wire_group_t;

#define LOCAL_ARRAY_SIZE 64

struct frame_t {
    size_t cursor;
    const function_t *function;
    array_t *local_array;
    free_wire_group_t *first_free_wire_group;
    free_wire_group_t *second_free_wire_group;
};

struct free_wire_group_t {
    const node_def_t *node_def;
    wire_t **wires;
};

static free_wire_group_t *
free_wire_group_new(const node_def_t *node_def) {
    free_wire_group_t *self = new(free_wire_group_t);
    self->node_def = node_def;
    self->wires = allocate_pointers(node_def->arity);
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
frame_new(const function_t *function) {
    frame_t *self = new(frame_t);
    self->cursor = 0;
    self->function = function;
    self->local_array = array_new(LOCAL_ARRAY_SIZE);
    return self;
}

void
frame_destroy(frame_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        frame_t *self = *self_pointer;
        array_destroy(&self->local_array);
        free_wire_group_destroy(&self->first_free_wire_group);
        free_wire_group_destroy(&self->second_free_wire_group);
        free(self);
        *self_pointer = NULL;
    }
}

static free_wire_group_t *
collect_free_wires_from_node(node_t *node) {
    free_wire_group_t *free_wire_group = free_wire_group_new(node->def);
    for (port_index_t i = 0; i < node->def->arity; i++) {
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
    wire_t *second_wire = wire->opposite;

    self->first_free_wire_group = collect_free_wires_from_node(first_wire->node);
    self->second_free_wire_group = collect_free_wires_from_node(second_wire->node);

    wire_destroy(&first_wire);
    wire_destroy(&second_wire);
}

wire_t *
frame_use_free_wire(
    frame_t *self,
    const node_def_t *node_def,
    port_index_t index
) {
    if (node_def == self->first_free_wire_group->node_def) {
        wire_t *free_wire = self->first_free_wire_group->wires[index];
        self->first_free_wire_group->wires[index] = NULL;
        if (!free_wire) {
            fprintf(stderr,
                    "[frame_use_free_wire] (%s) no wire at index: %i",
                    node_def->name,
                    index);
            assert(free_wire);
        }

        return free_wire;
    }

    if (node_def == self->second_free_wire_group->node_def) {
        wire_t *free_wire = self->second_free_wire_group->wires[index];
        self->second_free_wire_group->wires[index] = NULL;
        if (!free_wire) {
            fprintf(stderr,
                    "[frame_use_free_wire] (%s) no wire at index: %i",
                    node_def->name,
                    index);
            assert(free_wire);
        }

        return free_wire;
    }

    assert(false);
}

bool
frame_is_finished(const frame_t *self) {
    return self->cursor == function_length(self->function);
}

op_t *
frame_fetch_op(frame_t *self) {
    op_t *op = function_get_op(self->function, self->cursor);
    self->cursor++;
    return op;
}

static void
free_wire_group_print(const free_wire_group_t *free_wire_group, file_t *file) {
    for (port_index_t i = 0; i < free_wire_group->node_def->arity; i++) {
        wire_t *free_wire = free_wire_group->wires[i];
        if (!free_wire) continue;

        fprintf(file, "(%s)-%s => ",
                free_wire_group->node_def->name,
                free_wire_group->node_def->port_defs[i]->name);
        wire_print_reverse(free_wire, file);
        fprintf(file, "\n");
    }
}

void
frame_print(const frame_t *self, file_t *file) {
    fprintf(file, "<frame>\n");

    fprintf(file, "<function>\n");
    fprintf(file, ". ");
    function_print_with_cursor(self->function, file, self->cursor);
    fprintf(file, "\n");
    fprintf(file, "</function>\n");

    fprintf(file, "<local-free-wires>\n");
    if (self->first_free_wire_group)
        free_wire_group_print(self->first_free_wire_group, file);
    if (self->second_free_wire_group)
        free_wire_group_print(self->second_free_wire_group, file);
    fprintf(file, "</local-free-wires>\n");

    fprintf(file, "</frame>\n");
}

value_t
frame_local_get(const frame_t *self, size_t index) {
    return array_get(self->local_array, index);
}

void
frame_local_set(frame_t *self, size_t index, value_t value) {
    array_set(self->local_array, index, value);
}
