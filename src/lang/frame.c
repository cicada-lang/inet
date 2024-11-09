#include "index.h"

// The free ports in a frame can be referenced by `op_fpt_t`.

typedef struct free_port_group_t free_port_group_t;

struct frame_t {
    size_t program_counter;
    const program_t *program;
    free_port_group_t *first_free_port_group;
    free_port_group_t *second_free_port_group;
};

// A `port_t` is a free port
// if it is not linked to a node
// and it's `index` is -1.

// `free_port_group_t` does NOT own ports in `port_array`.

struct free_port_group_t {
    const node_spec_t *node_spec;
    port_t **port_array;
};

// static
free_port_group_t *
free_port_group_new(const node_spec_t *node_spec) {
    free_port_group_t *self = allocate(sizeof(free_port_group_t));
    self->node_spec = node_spec;
    self->port_array = allocate_pointer_array(node_spec->arity);
    return self;
}

static void
free_port_group_destroy(free_port_group_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        free_port_group_t *self = *self_pointer;
        free(self->port_array);
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
        free_port_group_destroy(&self->first_free_port_group);
        free_port_group_destroy(&self->second_free_port_group);
        free(self);
        *self_pointer = NULL;
    }
}

void
frame_collect_free_ports(frame_t *self, edge_t *active_edge) {
    port_t *first_port = active_edge->first_port;
    port_t *second_port = active_edge->second_port;

    edge_destroy(&active_edge);

    node_t *first_node = first_port->node;
    node_t *second_node = second_port->node;

    self->first_free_port_group = free_port_group_new(first_node->spec);
    for (size_t i = 0; i < first_node->spec->arity; i++) {
        if (port_is_principal(first_node->port_array[i])) {
            assert(first_node->port_array[i] == first_port);
            self->first_free_port_group->port_array[i] = NULL;
        } else {
            self->first_free_port_group->port_array[i] = first_node->port_array[i];
        }
    }

    self->second_free_port_group = free_port_group_new(second_node->spec);
    for (size_t i = 0; i < second_node->spec->arity; i++) {
        if (port_is_principal(second_node->port_array[i])) {
            assert(first_node->port_array[i] == second_port);
            self->second_free_port_group->port_array[i] = NULL;
        } else {
            self->second_free_port_group->port_array[i] = second_node->port_array[i];
        }
    }

    node_destroy(&first_node);
    node_destroy(&second_node);

    port_destroy(&first_port);
    port_destroy(&second_port);
}
