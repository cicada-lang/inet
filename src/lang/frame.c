#include "index.h"

// The free ports in a frame can be referenced by `op_get_free_port_t`.

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

// `free_port_group_t` does NOT own ports in `ports`.

struct free_port_group_t {
    const node_spec_t *node_spec;
    port_t **ports;
};

// static
free_port_group_t *
free_port_group_new(const node_spec_t *node_spec) {
    free_port_group_t *self = allocate(sizeof(free_port_group_t));
    self->node_spec = node_spec;
    self->ports = allocate_pointers(node_spec->arity);
    return self;
}

static void
free_port_group_destroy(free_port_group_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        free_port_group_t *self = *self_pointer;
        free(self->ports);
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

static free_port_group_t *
collect_free_ports_from_node(node_t *node) {
    free_port_group_t *free_port_group = free_port_group_new(node->spec);
    for (size_t i = 0; i < node->spec->arity; i++) {
        if (port_is_principal(node->ports[i])) {
            free_port_group->ports[i] = NULL;
        } else {
            port_t *port = node->ports[i];
            port_free_from_node(port);
            free_port_group->ports[i] = port;
        }
    }

    node_destroy(&node);
    return free_port_group;
}

void
frame_collect_free_ports(frame_t *self, active_pair_t *active_pair) {
    port_t *first_port = active_pair->first_port;
    port_t *second_port = active_pair->second_port;

    self->first_free_port_group = collect_free_ports_from_node(first_port->node);
    self->second_free_port_group = collect_free_ports_from_node(second_port->node);

    port_destroy(&first_port);
    port_destroy(&second_port);

    active_pair_destroy(&active_pair);
}

port_t *
frame_get_free_port(
    frame_t *self,
    const node_spec_t *node_spec,
    port_index_t index
) {
    if (node_spec == self->first_free_port_group->node_spec)
        return self->first_free_port_group->ports[index];
    if (node_spec == self->second_free_port_group->node_spec)
        return self->second_free_port_group->ports[index];
    assert(false);
}
